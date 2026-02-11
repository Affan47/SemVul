sqrt_emit(
   const struct lp_build_tgsi_action * action,
   struct lp_build_tgsi_context * bld_base,
   struct lp_build_emit_data * emit_data)
{
   if (bld_base->sqrt_action.emit) {
      bld_base->sqrt_action.emit(&bld_base->sqrt_action, bld_base, emit_data);
   } else {
      emit_data->output[emit_data->chan] = bld_base->base.undef;
   }
}
