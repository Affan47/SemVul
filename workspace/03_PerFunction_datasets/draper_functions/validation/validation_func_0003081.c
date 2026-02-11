block_has_only_trap (basic_block bb)
{
  rtx trap;


  if (bb == EXIT_BLOCK_PTR)
    return NULL_RTX;


  if (EDGE_COUNT (bb->succs) > 0)
    return NULL_RTX;


  trap = first_active_insn (bb);
  if (! (trap == BB_END (bb)
	 && GET_CODE (PATTERN (trap)) == TRAP_IF
         && TRAP_CONDITION (PATTERN (trap)) == const_true_rtx))
    return NULL_RTX;

  return trap;
}
