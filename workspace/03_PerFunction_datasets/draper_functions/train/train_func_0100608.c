fc_fcp_abts_resp(struct fc_fcp_pkt *fsp, struct fc_frame *fp)
{
	int ba_done = 1;
	struct fc_ba_rjt *brp;
	struct fc_frame_header *fh;

	fh = fc_frame_header_get(fp);
	switch (fh->fh_r_ctl) {
	case FC_RCTL_BA_ACC:
		break;
	case FC_RCTL_BA_RJT:
		brp = fc_frame_payload_get(fp, sizeof(*brp));
		if (brp && brp->br_reason == FC_BA_RJT_LOG_ERR)
			break;

	default:


		ba_done = 0;
	}

	if (ba_done) {
		fsp->state |= FC_SRB_ABORTED;
		fsp->state &= ~FC_SRB_ABORT_PENDING;

		if (fsp->wait_for_comp)
			complete(&fsp->tm_done);
		else
			fc_fcp_complete_locked(fsp);
	}
}
