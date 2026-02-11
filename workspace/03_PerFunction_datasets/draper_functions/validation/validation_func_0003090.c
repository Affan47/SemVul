lpfc_sli4_fcf_scan_read_fcf_rec(struct lpfc_hba *phba, uint16_t fcf_index)
{
	int rc = 0, error;
	LPFC_MBOXQ_t *mboxq;

	phba->fcoe_eventtag_at_fcf_scan = phba->fcoe_eventtag;
	phba->fcoe_cvl_eventtag_attn = phba->fcoe_cvl_eventtag;
	mboxq = mempool_alloc(phba->mbox_mem_pool, GFP_KERNEL);
	if (!mboxq) {
		lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
				"2000 Failed to allocate mbox for "
				"READ_FCF cmd\n");
		error = -ENOMEM;
		goto fail_fcf_scan;
	}

	rc = lpfc_sli4_mbx_read_fcf_rec(phba, mboxq, fcf_index);
	if (rc) {
		error = -EINVAL;
		goto fail_fcf_scan;
	}

	mboxq->vport = phba->pport;
	mboxq->mbox_cmpl = lpfc_mbx_cmpl_fcf_scan_read_fcf_rec;

	spin_lock_irq(&phba->hbalock);
	phba->hba_flag |= FCF_TS_INPROG;
	spin_unlock_irq(&phba->hbalock);

	rc = lpfc_sli_issue_mbox(phba, mboxq, MBX_NOWAIT);
	if (rc == MBX_NOT_FINISHED)
		error = -EIO;
	else {

		if (fcf_index == LPFC_FCOE_FCF_GET_FIRST)
			phba->fcf.eligible_fcf_cnt = 0;
		error = 0;
	}
fail_fcf_scan:
	if (error) {
		if (mboxq)
			lpfc_sli4_mbox_cmd_free(phba, mboxq);

		spin_lock_irq(&phba->hbalock);
		phba->hba_flag &= ~FCF_TS_INPROG;
		spin_unlock_irq(&phba->hbalock);
	}
	return error;
}
