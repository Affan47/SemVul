lpfc_bsg_issue_mbox_ext_handle_job(struct lpfc_hba *phba, LPFC_MBOXQ_t *pmboxq)
{
	struct bsg_job_data *dd_data;
	struct fc_bsg_job *job;
	uint8_t *pmb, *pmb_buf;
	unsigned long flags;
	uint32_t size;
	int rc = 0;
	struct lpfc_dmabuf *dmabuf;
	struct lpfc_sli_config_mbox *sli_cfg_mbx;
	uint8_t *pmbx;

	dd_data = pmboxq->context1;


	spin_lock_irqsave(&phba->ct_ev_lock, flags);
	job = dd_data->set_job;
	if (job) {

		job->dd_data = NULL;
	}
	spin_unlock_irqrestore(&phba->ct_ev_lock, flags);


	pmb = (uint8_t *)&pmboxq->u.mb;
	pmb_buf = (uint8_t *)dd_data->context_un.mbox.mb;

	memcpy(pmb_buf, pmb, sizeof(MAILBOX_t));

	dmabuf = phba->mbox_ext_buf_ctx.mbx_dmabuf;
	sli_cfg_mbx = (struct lpfc_sli_config_mbox *)dmabuf->virt;
	if (!bsg_bf_get(lpfc_mbox_hdr_emb,
	    &sli_cfg_mbx->un.sli_config_emb0_subsys.sli_config_hdr)) {
		pmbx = (uint8_t *)dmabuf->virt;

		lpfc_sli_pcimem_bcopy(&pmbx[sizeof(MAILBOX_t)],
			&pmbx[sizeof(MAILBOX_t)],
			sli_cfg_mbx->un.sli_config_emb0_subsys.mse[0].buf_len);
	}


	if (job) {
		size = job->reply_payload.payload_len;
		job->reply->reply_payload_rcv_len =
			sg_copy_from_buffer(job->reply_payload.sg_list,
					    job->reply_payload.sg_cnt,
					    pmb_buf, size);


		job->reply->result = 0;

		lpfc_printf_log(phba, KERN_INFO, LOG_LIBDFC,
				"2937 SLI_CONFIG ext-buffer maibox command "
				"(x%x/x%x) complete bsg job done, bsize:%d\n",
				phba->mbox_ext_buf_ctx.nembType,
				phba->mbox_ext_buf_ctx.mboxType, size);
		lpfc_idiag_mbxacc_dump_bsg_mbox(phba,
					phba->mbox_ext_buf_ctx.nembType,
					phba->mbox_ext_buf_ctx.mboxType,
					dma_ebuf, sta_pos_addr,
					phba->mbox_ext_buf_ctx.mbx_dmabuf, 0);
	} else {
		lpfc_printf_log(phba, KERN_ERR, LOG_LIBDFC,
				"2938 SLI_CONFIG ext-buffer maibox "
				"command (x%x/x%x) failure, rc:x%x\n",
				phba->mbox_ext_buf_ctx.nembType,
				phba->mbox_ext_buf_ctx.mboxType, rc);
	}


	phba->mbox_ext_buf_ctx.state = LPFC_BSG_MBOX_DONE;
	kfree(dd_data);
	return job;
}
