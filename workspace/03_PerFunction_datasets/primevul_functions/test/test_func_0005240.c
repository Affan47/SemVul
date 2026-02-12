static void scalar_min_max_arsh(struct bpf_reg_state *dst_reg,
				struct bpf_reg_state *src_reg)
{
	u64 umin_val = src_reg->umin_value;


	dst_reg->smin_value >>= umin_val;
	dst_reg->smax_value >>= umin_val;

	dst_reg->var_off = tnum_arshift(dst_reg->var_off, umin_val, 64);


	dst_reg->umin_value = 0;
	dst_reg->umax_value = U64_MAX;


	__mark_reg32_unbounded(dst_reg);
	__update_reg_bounds(dst_reg);
}
