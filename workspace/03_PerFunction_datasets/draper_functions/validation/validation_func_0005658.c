compute_regs_asm_clobbered (void)
{
  basic_block bb;

  FOR_EACH_BB (bb)
    {
      rtx insn;
      FOR_BB_INSNS_REVERSE (bb, insn)
	{
	  df_ref *def_rec;

	  if (insn_contains_asm (insn))
	    for (def_rec = DF_INSN_DEFS (insn); *def_rec; def_rec++)
	      {
		df_ref def = *def_rec;
		unsigned int dregno = DF_REF_REGNO (def);
		if (dregno < FIRST_PSEUDO_REGISTER)
		  {
		    unsigned int i;
		    enum machine_mode mode = GET_MODE (DF_REF_REAL_REG (def));
		    unsigned int end = dregno
		      + hard_regno_nregs[dregno][mode] - 1;

		    for (i = dregno; i <= end; ++i)
		      SET_HARD_REG_BIT(crtl->asm_clobbers, i);
		  }
	      }
	}
    }
}
