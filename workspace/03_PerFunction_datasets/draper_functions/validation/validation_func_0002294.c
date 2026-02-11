loop_single_full_bb_p (struct loop *loop)
{
  unsigned i;
  basic_block *bbs = get_loop_body (loop);

  for (i = 0; i < loop->num_nodes ; i++)
    {
      rtx head, tail;
      bool empty_bb = true;

      if (bbs[i] == loop->header)
        continue;


      get_ebb_head_tail (bbs[i], bbs[i], &head, &tail);
      for (; head != NEXT_INSN (tail); head = NEXT_INSN (head))
        {
          if (NOTE_P (head) || LABEL_P (head)
 	      || (INSN_P (head) && (DEBUG_INSN_P (head) || JUMP_P (head))))
 	    continue;
 	  empty_bb = false;
 	  break;
        }

      if (! empty_bb)
        {
          free (bbs);
          return false;
        }
    }
  free (bbs);
  return true;
}
