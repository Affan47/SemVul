static void scalar_min_max_mul(struct bpf_reg_state *dst_reg,
			       struct bpf_reg_state *src_reg)
{
	s64 smin_val = src_reg->smin_value;
	u64 umin_val = src_reg->umin_value;
	u64 umax_val = src_reg->umax_value;

	dst_reg->var_off = tnum_mul(dst_reg->var_off, src_reg->var_off);
	if (smin_val < 0 || dst_reg->smin_value < 0) {

		__mark_reg_unbounded(dst_reg);
		__update_reg_bounds(dst_reg);
		return;
	}


	if (umax_val > U32_MAX || dst_reg->umax_value > U32_MAX) {

		__mark_reg_unbounded(dst_reg);

		__update_reg_bounds(dst_reg);
		return;
	}
	dst_reg->umin_value *= umin_val;
	dst_reg->umax_value *= umax_val;
	if (dst_reg->umax_value > S64_MAX) {

		dst_reg->smin_value = S64_MIN;
		dst_reg->smax_value = S64_MAX;
	} else {
		dst_reg->smin_value = dst_reg->umin_value;
		dst_reg->smax_value = dst_reg->umax_value;
	}
}
