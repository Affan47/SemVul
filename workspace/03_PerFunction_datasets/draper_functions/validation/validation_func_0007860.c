__bfa_cb_ioim_comp(void *cbarg, bfa_boolean_t complete)
{
	struct bfa_ioim_s	*ioim = cbarg;
	struct bfi_ioim_rsp_s *m;
	u8	*snsinfo = NULL;
	u8	sns_len = 0;
	s32	residue = 0;

	if (!complete) {
		bfa_sm_send_event(ioim, BFA_IOIM_SM_HCB);
		return;
	}

	m = (struct bfi_ioim_rsp_s *) &ioim->iosp->comp_rspmsg;
	if (m->io_status == BFI_IOIM_STS_OK) {


		if ((m->scsi_status == SCSI_STATUS_CHECK_CONDITION) &&
					m->sns_len) {
			sns_len = m->sns_len;
			snsinfo = BFA_SNSINFO_FROM_TAG(ioim->fcpim->fcp,
						ioim->iotag);
		}


		if (m->resid_flags == FCP_RESID_UNDER) {
			residue = be32_to_cpu(m->residue);
			bfa_stats(ioim->itnim, iocomp_underrun);
		}
		if (m->resid_flags == FCP_RESID_OVER) {
			residue = be32_to_cpu(m->residue);
			residue = -residue;
			bfa_stats(ioim->itnim, iocomp_overrun);
		}
	}

	bfa_cb_ioim_done(ioim->bfa->bfad, ioim->dio, m->io_status,
			  m->scsi_status, sns_len, snsinfo, residue);
}
