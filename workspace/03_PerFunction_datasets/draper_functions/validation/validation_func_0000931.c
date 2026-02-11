cprop_find_used_regs_1 (rtx *loc, void *data)
{
  if (REG_P (*loc))
    {
      struct value_data *vd = (struct value_data *) data;
      if (vd->e[REGNO (*loc)].debug_insn_changes)
	{
	  apply_debug_insn_changes (vd, REGNO (*loc));
	  free_debug_insn_changes (vd, REGNO (*loc));
	}
    }
  return 0;
}
