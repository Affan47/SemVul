trivially_empty_bb_p (basic_block bb)
{
  rtx insn = BB_END (bb);

  while (1)
    {
      if (insn == BB_HEAD (bb))
	return true;
      if (!DEBUG_INSN_P (insn))
	return false;
      insn = PREV_INSN (insn);
    }
}
