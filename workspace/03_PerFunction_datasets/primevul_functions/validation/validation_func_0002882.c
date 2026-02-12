static void scalar_min_max_and(struct bpf_reg_state *dst_reg,
			       struct bpf_reg_state *src_reg)
{
	s64 smin_val = src_reg->smin_value;
	u64 umax_val = src_reg->umax_value;


	dst_reg->var_off = tnum_and(dst_reg->var_off, src_reg->var_off);
	dst_reg->umin_value = dst_reg->var_off.value;
	dst_reg->umax_value = min(dst_reg->umax_value, umax_val);
	if (dst_reg->smin_value < 0 || smin_val < 0) {


		dst_reg->smin_value = S64_MIN;
		dst_reg->smax_value = S64_MAX;
	} else {


		dst_reg->smin_value = dst_reg->umin_value;
		dst_reg->smax_value = dst_reg->umax_value;
	}

	__update_reg_bounds(dst_reg);
}
