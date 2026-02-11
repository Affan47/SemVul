find_moveable_store (rtx insn, int *regs_set_before, int *regs_set_after)
{
  struct ls_expr * ptr;
  rtx dest, set, tmp;
  int check_anticipatable, check_available;
  basic_block bb = BLOCK_FOR_INSN (insn);

  set = single_set (insn);
  if (!set)
    return;

  dest = SET_DEST (set);

  if (GET_CODE (dest) != MEM || MEM_VOLATILE_P (dest)
      || GET_MODE (dest) == BLKmode)
    return;

  if (side_effects_p (dest))
    return;


  if (flag_non_call_exceptions && may_trap_p (dest))
    return;

  ptr = ldst_entry (dest);
  if (!ptr->pattern_regs)
    ptr->pattern_regs = extract_mentioned_regs (dest);


  check_anticipatable = 0;
  if (!ANTIC_STORE_LIST (ptr))
    check_anticipatable = 1;
  else
    {
      tmp = XEXP (ANTIC_STORE_LIST (ptr), 0);
      if (tmp != NULL_RTX
	  && BLOCK_FOR_INSN (tmp) != bb)
	check_anticipatable = 1;
    }
  if (check_anticipatable)
    {
      if (store_killed_before (dest, ptr->pattern_regs, insn, bb, regs_set_before))
	tmp = NULL_RTX;
      else
	tmp = insn;
      ANTIC_STORE_LIST (ptr) = alloc_INSN_LIST (tmp,
						ANTIC_STORE_LIST (ptr));
    }


  check_available = 0;
  if (!AVAIL_STORE_LIST (ptr))
    check_available = 1;
  else
    {
      tmp = XEXP (AVAIL_STORE_LIST (ptr), 0);
      if (BLOCK_FOR_INSN (tmp) != bb)
	check_available = 1;
    }
  if (check_available)
    {


      if (LAST_AVAIL_CHECK_FAILURE (ptr))
	{
	  for (tmp = BB_END (bb);
	       tmp != insn && tmp != LAST_AVAIL_CHECK_FAILURE (ptr);
	       tmp = PREV_INSN (tmp))
	    continue;
	  if (tmp == insn)
	    check_available = 0;
	}
      else
	check_available = store_killed_after (dest, ptr->pattern_regs, insn,
					      bb, regs_set_after,
					      &LAST_AVAIL_CHECK_FAILURE (ptr));
    }
  if (!check_available)
    AVAIL_STORE_LIST (ptr) = alloc_INSN_LIST (insn, AVAIL_STORE_LIST (ptr));
}
