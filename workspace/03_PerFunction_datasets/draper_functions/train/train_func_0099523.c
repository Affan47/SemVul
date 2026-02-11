schedule_ebb (head, tail)
     rtx head, tail;
{
  int n_insns;
  struct deps tmp_deps;

  if (no_real_insns_p (head, tail))
    return;

  init_deps_global ();


  init_deps (&tmp_deps);
  sched_analyze (&tmp_deps, head, tail);
  free_deps (&tmp_deps);


  compute_forward_dependences (head, tail);


  n_insns = set_priorities (head, tail);

  current_sched_info->prev_head = PREV_INSN (head);
  current_sched_info->next_tail = NEXT_INSN (tail);

  if (write_symbols != NO_DEBUG)
    {
      save_line_notes (0, head, tail);
      rm_line_notes (head, tail);
    }


  if (INSN_P (head))
    {
      rtx note;

      for (note = REG_NOTES (head); note; note = XEXP (note, 1))
	if (REG_NOTE_KIND (note) == REG_SAVE_NOTE)
	  {
	    remove_note (head, note);
	    note = XEXP (note, 1);
	    remove_note (head, note);
	  }
    }


  rm_other_notes (head, tail);

  current_sched_info->queue_must_finish_empty = 1;

  schedule_block (-1, n_insns);


  if (sched_n_insns != n_insns)
    abort ();
  head = current_sched_info->head;
  tail = current_sched_info->tail;

  if (write_symbols != NO_DEBUG)
    restore_line_notes (head, tail);

  finish_deps_global ();
}
