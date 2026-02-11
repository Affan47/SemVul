set_us_coefficients(struct vpe_ctx *ctx)
{
	struct vpe_mmr_adb *mmr_adb = ctx->mmr_adb.addr;
	struct vpe_q_data *s_q_data = &ctx->q_data[Q_DATA_SRC];
	u32 *us1_reg = &mmr_adb->us1_regs[0];
	u32 *us2_reg = &mmr_adb->us2_regs[0];
	u32 *us3_reg = &mmr_adb->us3_regs[0];
	const unsigned short *cp, *end_cp;

	cp = &us_coeffs[0].anchor_fid0_c0;

	if (s_q_data->flags & Q_DATA_INTERLACED)
		cp += sizeof(us_coeffs[0]) / sizeof(*cp);

	end_cp = cp + sizeof(us_coeffs[0]) / sizeof(*cp);

	while (cp < end_cp) {
		write_field(us1_reg, *cp++, VPE_US_C0_MASK, VPE_US_C0_SHIFT);
		write_field(us1_reg, *cp++, VPE_US_C1_MASK, VPE_US_C1_SHIFT);
		*us2_reg++ = *us1_reg;
		*us3_reg++ = *us1_reg++;
	}
	ctx->load_mmrs = true;
}
