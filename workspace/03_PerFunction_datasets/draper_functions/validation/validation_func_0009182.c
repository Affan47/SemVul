record_promoted_value (rtx insn, rtx subreg)
{
  struct insn_link *links;
  rtx set;
  unsigned int regno = REGNO (SUBREG_REG (subreg));
  enum machine_mode mode = GET_MODE (subreg);

  if (GET_MODE_PRECISION (mode) > HOST_BITS_PER_WIDE_INT)
    return;

  for (links = LOG_LINKS (insn); links;)
    {
      reg_stat_type *rsp;

      insn = links->insn;
      set = single_set (insn);

      if (! set || !REG_P (SET_DEST (set))
	  || REGNO (SET_DEST (set)) != regno
	  || GET_MODE (SET_DEST (set)) != GET_MODE (SUBREG_REG (subreg)))
	{
	  links = links->next;
	  continue;
	}

      rsp = VEC_index (reg_stat_type, reg_stat, regno);
      if (rsp->last_set == insn)
	{
	  if (SUBREG_PROMOTED_UNSIGNED_P (subreg) > 0)
	    rsp->last_set_nonzero_bits &= GET_MODE_MASK (mode);
	}

      if (REG_P (SET_SRC (set)))
	{
	  regno = REGNO (SET_SRC (set));
	  links = LOG_LINKS (insn);
	}
      else
	break;
    }
}
