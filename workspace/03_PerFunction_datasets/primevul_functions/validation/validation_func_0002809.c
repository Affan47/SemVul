static void scalar_min_max_lsh(struct bpf_reg_state *dst_reg,
			       struct bpf_reg_state *src_reg)
{
	u64 umax_val = src_reg->umax_value;
	u64 umin_val = src_reg->umin_value;


	dst_reg->smin_value = S64_MIN;
	dst_reg->smax_value = S64_MAX;

	if (dst_reg->umax_value > 1ULL << (63 - umax_val)) {
		dst_reg->umin_value = 0;
		dst_reg->umax_value = U64_MAX;
	} else {
		dst_reg->umin_value <<= umin_val;
		dst_reg->umax_value <<= umax_val;
	}
	dst_reg->var_off = tnum_lshift(dst_reg->var_off, umin_val);

	__update_reg_bounds(dst_reg);
}
