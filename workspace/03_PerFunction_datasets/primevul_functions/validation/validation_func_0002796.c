static void scalar_min_max_arsh(struct bpf_reg_state *dst_reg,
			        struct bpf_reg_state *src_reg,
				u64 insn_bitness)
{
	u64 umin_val = src_reg->umin_value;


	if (insn_bitness == 32) {
		dst_reg->smin_value = (u32)(((s32)dst_reg->smin_value) >> umin_val);
		dst_reg->smax_value = (u32)(((s32)dst_reg->smax_value) >> umin_val);
	} else {
		dst_reg->smin_value >>= umin_val;
		dst_reg->smax_value >>= umin_val;
	}

	dst_reg->var_off = tnum_arshift(dst_reg->var_off, umin_val,
					insn_bitness);


	dst_reg->umin_value = 0;
	dst_reg->umax_value = U64_MAX;
	__update_reg_bounds(dst_reg);
}
