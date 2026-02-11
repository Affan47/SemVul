expand_continue_loop (whichloop)
     struct nesting *whichloop;
{

  rtx note;

  if (flag_guess_branch_prob)
    {
      note = emit_note (NULL, NOTE_INSN_PREDICTION);
      NOTE_PREDICTION (note) = NOTE_PREDICT (PRED_CONTINUE, IS_TAKEN);
    }
  clear_last_expr ();
  if (whichloop == 0)
    whichloop = loop_stack;
  if (whichloop == 0)
    return 0;
  expand_goto_internal (NULL_TREE, whichloop->data.loop.continue_label,
			NULL_RTX);
  return 1;
}
