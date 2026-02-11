is_cfg_nonregular (void)
{
  basic_block b;
  rtx insn;


  if (nonlocal_goto_handler_labels)
    return 1;


  if (forced_labels)
    return 1;


  if (current_function_has_exception_handlers ())
    return 1;


  FOR_EACH_BB (b)
    FOR_BB_INSNS (b, insn)
      {
	rtx note, next, set, dest;


	if (JUMP_P (insn) && computed_jump_p (insn))
	  return 1;

	if (!INSN_P (insn))
	  continue;

	note = find_reg_note (insn, REG_LABEL_OPERAND, NULL_RTX);
	if (note == NULL_RTX)
	  continue;


	next = next_nonnote_insn (insn);
	if (next == NULL_RTX
	    || !JUMP_P (next)
	    || (JUMP_LABEL (next) != XEXP (note, 0)
		&& find_reg_note (next, REG_LABEL_TARGET,
				  XEXP (note, 0)) == NULL_RTX)
	    || BLOCK_FOR_INSN (insn) != BLOCK_FOR_INSN (next))
	  return 1;

	set = single_set (insn);
	if (set == NULL_RTX)
	  return 1;

	dest = SET_DEST (set);
	if (!REG_P (dest) || !dead_or_set_p (next, dest))
	  return 1;
      }


  FOR_EACH_BB (b)
    {
      if (EDGE_COUNT (b->preds) == 0
	  || (single_pred_p (b)
	      && single_pred (b) == b))
	return 1;
    }


  return 0;
}
