save_parm_insns (insn, first_nonparm_insn)
     rtx insn;
     rtx first_nonparm_insn;
{
  if (insn == NULL_RTX)
    return;

  for (insn = NEXT_INSN (insn); insn; insn = NEXT_INSN (insn))
    {
      if (insn == first_nonparm_insn)
	in_nonparm_insns = 1;

      if (INSN_P (insn))
	{

	  note_stores (PATTERN (insn), note_modified_parmregs, NULL);


	  if (GET_CODE (insn) == CALL_INSN
	      && GET_CODE (PATTERN (insn)) == CALL_PLACEHOLDER)
	    {
	      int i;

	      for (i = 0; i < 3; i++)
		save_parm_insns (XEXP (PATTERN (insn), i),
				 first_nonparm_insn);
	    }
	}
    }
}
