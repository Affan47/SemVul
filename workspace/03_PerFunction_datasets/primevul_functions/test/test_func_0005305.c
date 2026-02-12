static void __reg32_deduce_bounds(struct bpf_reg_state *reg)
{


	if (reg->s32_min_value >= 0 || reg->s32_max_value < 0) {
		reg->s32_min_value = reg->u32_min_value =
			max_t(u32, reg->s32_min_value, reg->u32_min_value);
		reg->s32_max_value = reg->u32_max_value =
			min_t(u32, reg->s32_max_value, reg->u32_max_value);
		return;
	}


	if ((s32)reg->u32_max_value >= 0) {


		reg->s32_min_value = reg->u32_min_value;
		reg->s32_max_value = reg->u32_max_value =
			min_t(u32, reg->s32_max_value, reg->u32_max_value);
	} else if ((s32)reg->u32_min_value < 0) {


		reg->s32_min_value = reg->u32_min_value =
			max_t(u32, reg->s32_min_value, reg->u32_min_value);
		reg->s32_max_value = reg->u32_max_value;
	}
}
