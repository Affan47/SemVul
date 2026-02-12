static void __reg_combine_32_into_64(struct bpf_reg_state *reg)
{


	if (tnum_equals_const(tnum_clear_subreg(reg->var_off), 0)) {
		__reg_assign_32_into_64(reg);
	} else {


		__mark_reg64_unbounded(reg);
		__update_reg_bounds(reg);
	}


	__reg_deduce_bounds(reg);
	__reg_bound_offset(reg);
	__update_reg_bounds(reg);
}
