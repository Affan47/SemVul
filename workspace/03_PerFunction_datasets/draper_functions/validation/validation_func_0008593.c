sym_compute_residual(struct sym_hcb *np, struct sym_ccb *cp)
{
	int dp_sg, dp_sgmin, resid = 0;
	int dp_ofs = 0;


	if (cp->xerr_status & (XE_EXTRA_DATA|XE_SODL_UNRUN|XE_SWIDE_OVRUN)) {
		if (cp->xerr_status & XE_EXTRA_DATA)
			resid -= cp->extra_bytes;
		if (cp->xerr_status & XE_SODL_UNRUN)
			++resid;
		if (cp->xerr_status & XE_SWIDE_OVRUN)
			--resid;
	}


	if (cp->phys.head.lastp == cp->goalp)
		return resid;


	if (cp->startp == cp->phys.head.lastp ||
	    sym_evaluate_dp(np, cp, scr_to_cpu(cp->phys.head.lastp),
			    &dp_ofs) < 0) {
		return cp->data_len - cp->odd_byte_adjustment;
	}


	if (cp->host_flags & HF_SENSE) {
		return -dp_ofs;
	}


	dp_sgmin = SYM_CONF_MAX_SG - cp->segments;
	resid = -cp->ext_ofs;
	for (dp_sg = cp->ext_sg; dp_sg < SYM_CONF_MAX_SG; ++dp_sg) {
		u_int tmp = scr_to_cpu(cp->phys.data[dp_sg].size);
		resid += (tmp & 0xffffff);
	}

	resid -= cp->odd_byte_adjustment;


	return resid;
}
