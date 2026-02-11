constprop_register (rtx insn, rtx from, rtx to, int alter_jumps)
{
  rtx sset;


  if (alter_jumps
      && (sset = single_set (insn)) != NULL
      && NEXT_INSN (insn)
      && any_condjump_p (NEXT_INSN (insn)) && onlyjump_p (NEXT_INSN (insn)))
    {
      rtx dest = SET_DEST (sset);
      if ((REG_P (dest) || CC0_P (dest))
	  && cprop_jump (BLOCK_FOR_INSN (insn), insn, NEXT_INSN (insn), from, to))
	return 1;
    }


  if (GET_CODE (insn) == INSN
      && try_replace_reg (from, to, insn))
    return 1;


  else if (alter_jumps && any_condjump_p (insn) && onlyjump_p (insn))
    return cprop_jump (BLOCK_FOR_INSN (insn), NULL, insn, from, to);
  return 0;
}
