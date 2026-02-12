static void virtual_engine_initial_hint(struct virtual_engine *ve)
{
	int swp;


	swp = prandom_u32_max(ve->num_siblings);
	if (!swp)
		return;

	swap(ve->siblings[swp], ve->siblings[0]);
	if (!intel_engine_has_relative_mmio(ve->siblings[0]))
		virtual_update_register_offsets(ve->context.lrc_reg_state,
						ve->siblings[0]);
}
