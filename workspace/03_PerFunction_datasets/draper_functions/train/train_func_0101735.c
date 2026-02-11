reg_loc_descriptor (rtx rtl, enum var_init_status initialized)
{
  rtx regs;

  if (REGNO (rtl) >= FIRST_PSEUDO_REGISTER)
    return 0;


  if ((rtl == arg_pointer_rtx || rtl == frame_pointer_rtx)
      && eliminate_regs (rtl, VOIDmode, NULL_RTX) != rtl)
    {
      dw_loc_descr_ref result = NULL;

      if (dwarf_version >= 4 || !dwarf_strict)
	{
	  result = mem_loc_descriptor (rtl, GET_MODE (rtl), VOIDmode,
				       initialized);
	  if (result)
	    add_loc_descr (&result,
			   new_loc_descr (DW_OP_stack_value, 0, 0));
	}
      return result;
    }

  regs = targetm.dwarf_register_span (rtl);

  if (hard_regno_nregs[REGNO (rtl)][GET_MODE (rtl)] > 1 || regs)
    return multiple_reg_loc_descriptor (rtl, regs, initialized);
  else
    return one_reg_loc_descriptor (dbx_reg_number (rtl), initialized);
}
