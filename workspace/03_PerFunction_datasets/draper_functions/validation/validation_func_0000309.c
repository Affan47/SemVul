escp2_use_extended_commands(const stp_vars_t *v, int use_softweave)
{
  return (stp_escp2_has_cap(v, MODEL_COMMAND, MODEL_COMMAND_PRO) ||
	  (stp_escp2_has_cap(v, MODEL_VARIABLE_DOT, MODEL_VARIABLE_YES) &&
	   use_softweave));
}
