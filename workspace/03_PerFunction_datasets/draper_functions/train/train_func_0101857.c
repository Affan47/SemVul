lpfc_bsg_sli_cfg_dma_desc_setup(struct lpfc_hba *phba, enum nemb_type nemb_tp,
				uint32_t index, struct lpfc_dmabuf *mbx_dmabuf,
				struct lpfc_dmabuf *ext_dmabuf)
{
	struct lpfc_sli_config_mbox *sli_cfg_mbx;


	sli_cfg_mbx = (struct lpfc_sli_config_mbox *)mbx_dmabuf->virt;

	if (nemb_tp == nemb_mse) {
		if (index == 0) {
			sli_cfg_mbx->un.sli_config_emb0_subsys.
				mse[index].pa_hi =
				putPaddrHigh(mbx_dmabuf->phys +
					     sizeof(MAILBOX_t));
			sli_cfg_mbx->un.sli_config_emb0_subsys.
				mse[index].pa_lo =
				putPaddrLow(mbx_dmabuf->phys +
					    sizeof(MAILBOX_t));
			lpfc_printf_log(phba, KERN_INFO, LOG_LIBDFC,
					"2943 SLI_CONFIG(mse)[%d], "
					"bufLen:%d, addrHi:x%x, addrLo:x%x\n",
					index,
					sli_cfg_mbx->un.sli_config_emb0_subsys.
					mse[index].buf_len,
					sli_cfg_mbx->un.sli_config_emb0_subsys.
					mse[index].pa_hi,
					sli_cfg_mbx->un.sli_config_emb0_subsys.
					mse[index].pa_lo);
		} else {
			sli_cfg_mbx->un.sli_config_emb0_subsys.
				mse[index].pa_hi =
				putPaddrHigh(ext_dmabuf->phys);
			sli_cfg_mbx->un.sli_config_emb0_subsys.
				mse[index].pa_lo =
				putPaddrLow(ext_dmabuf->phys);
			lpfc_printf_log(phba, KERN_INFO, LOG_LIBDFC,
					"2944 SLI_CONFIG(mse)[%d], "
					"bufLen:%d, addrHi:x%x, addrLo:x%x\n",
					index,
					sli_cfg_mbx->un.sli_config_emb0_subsys.
					mse[index].buf_len,
					sli_cfg_mbx->un.sli_config_emb0_subsys.
					mse[index].pa_hi,
					sli_cfg_mbx->un.sli_config_emb0_subsys.
					mse[index].pa_lo);
		}
	} else {
		if (index == 0) {
			sli_cfg_mbx->un.sli_config_emb1_subsys.
				hbd[index].pa_hi =
				putPaddrHigh(mbx_dmabuf->phys +
					     sizeof(MAILBOX_t));
			sli_cfg_mbx->un.sli_config_emb1_subsys.
				hbd[index].pa_lo =
				putPaddrLow(mbx_dmabuf->phys +
					    sizeof(MAILBOX_t));
			lpfc_printf_log(phba, KERN_INFO, LOG_LIBDFC,
					"3007 SLI_CONFIG(hbd)[%d], "
					"bufLen:%d, addrHi:x%x, addrLo:x%x\n",
				index,
				bsg_bf_get(lpfc_mbox_sli_config_ecmn_hbd_len,
				&sli_cfg_mbx->un.
				sli_config_emb1_subsys.hbd[index]),
				sli_cfg_mbx->un.sli_config_emb1_subsys.
				hbd[index].pa_hi,
				sli_cfg_mbx->un.sli_config_emb1_subsys.
				hbd[index].pa_lo);

		} else {
			sli_cfg_mbx->un.sli_config_emb1_subsys.
				hbd[index].pa_hi =
				putPaddrHigh(ext_dmabuf->phys);
			sli_cfg_mbx->un.sli_config_emb1_subsys.
				hbd[index].pa_lo =
				putPaddrLow(ext_dmabuf->phys);
			lpfc_printf_log(phba, KERN_INFO, LOG_LIBDFC,
					"3008 SLI_CONFIG(hbd)[%d], "
					"bufLen:%d, addrHi:x%x, addrLo:x%x\n",
				index,
				bsg_bf_get(lpfc_mbox_sli_config_ecmn_hbd_len,
				&sli_cfg_mbx->un.
				sli_config_emb1_subsys.hbd[index]),
				sli_cfg_mbx->un.sli_config_emb1_subsys.
				hbd[index].pa_hi,
				sli_cfg_mbx->un.sli_config_emb1_subsys.
				hbd[index].pa_lo);
		}
	}
	return;
}
