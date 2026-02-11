remove_insn (insn)
     rtx insn;
{
  rtx next = NEXT_INSN (insn);
  rtx prev = PREV_INSN (insn);
  basic_block bb;

  if (prev)
    {
      NEXT_INSN (prev) = next;
      if (GET_CODE (prev) == INSN && GET_CODE (PATTERN (prev)) == SEQUENCE)
	{
	  rtx sequence = PATTERN (prev);
	  NEXT_INSN (XVECEXP (sequence, 0, XVECLEN (sequence, 0) - 1)) = next;
	}
    }
  else if (first_insn == insn)
    first_insn = next;
  else
    {
      struct sequence_stack *stack = seq_stack;

      for (; stack; stack = stack->next)
	if (insn == stack->first)
	  {
	    stack->first = next;
	    break;
	  }

      if (stack == 0)
	abort ();
    }

  if (next)
    {
      PREV_INSN (next) = prev;
      if (GET_CODE (next) == INSN && GET_CODE (PATTERN (next)) == SEQUENCE)
	PREV_INSN (XVECEXP (PATTERN (next), 0, 0)) = prev;
    }
  else if (last_insn == insn)
    last_insn = prev;
  else
    {
      struct sequence_stack *stack = seq_stack;

      for (; stack; stack = stack->next)
	if (insn == stack->last)
	  {
	    stack->last = prev;
	    break;
	  }

      if (stack == 0)
	abort ();
    }
  if (GET_CODE (insn) != BARRIER
      && (bb = BLOCK_FOR_INSN (insn)))
    {
      if (INSN_P (insn))
	bb->flags |= BB_DIRTY;
      if (bb->head == insn)
	{


	  if (GET_CODE (insn) == NOTE)
	    abort ();
	  bb->head = next;
	}
      if (bb->end == insn)
	bb->end = prev;
    }
}
