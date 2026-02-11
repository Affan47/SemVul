update_reg_equal_equiv_notes (rtx insn, enum machine_mode new_mode,
			      enum machine_mode old_mode, enum rtx_code code)
{
  rtx *loc = &REG_NOTES (insn);
  while (*loc)
    {
      enum reg_note kind = REG_NOTE_KIND (*loc);
      if (kind == REG_EQUAL || kind == REG_EQUIV)
	{
	  rtx orig_src = XEXP (*loc, 0);


	  if (GET_CODE (orig_src) == CONST_INT
	      && HOST_BITS_PER_WIDE_INT >= GET_MODE_BITSIZE (new_mode))
	    {
	      if (INTVAL (orig_src) >= 0 || code == SIGN_EXTEND)
		;
	      else
		{


		  rtx new_const_int
		    = gen_int_mode (INTVAL (orig_src)
				    & GET_MODE_MASK (old_mode),
				    new_mode);
		  if (!validate_change (insn, &XEXP (*loc, 0),
					new_const_int, true))
		    return false;
		}
	      loc = &XEXP (*loc, 1);
	    }

	  else if (!validate_change (insn, loc, XEXP (*loc, 1), true))
	    return false;
	}
      else
	loc = &XEXP (*loc, 1);
    }
  return true;
}
