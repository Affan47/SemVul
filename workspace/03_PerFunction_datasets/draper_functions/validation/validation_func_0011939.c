invalidate_for_call (void)
{
  unsigned int regno, endregno;
  unsigned int i;
  unsigned hash;
  struct table_elt *p, *next;
  int in_table = 0;


  for (regno = 0; regno < FIRST_PSEUDO_REGISTER; regno++)
    if (TEST_HARD_REG_BIT (regs_invalidated_by_call, regno))
      {
	delete_reg_equiv (regno);
	if (REG_TICK (regno) >= 0)
	  {
	    REG_TICK (regno)++;
	    SUBREG_TICKED (regno) = -1;
	  }

	in_table |= (TEST_HARD_REG_BIT (hard_regs_in_table, regno) != 0);
      }


  if (in_table)
    for (hash = 0; hash < HASH_SIZE; hash++)
      for (p = table[hash]; p; p = next)
	{
	  next = p->next_same_hash;

	  if (GET_CODE (p->exp) != REG
	      || REGNO (p->exp) >= FIRST_PSEUDO_REGISTER)
	    continue;

	  regno = REGNO (p->exp);
	  endregno = regno + HARD_REGNO_NREGS (regno, GET_MODE (p->exp));

	  for (i = regno; i < endregno; i++)
	    if (TEST_HARD_REG_BIT (regs_invalidated_by_call, i))
	      {
		remove_from_table (p, hash);
		break;
	      }
	}
}
