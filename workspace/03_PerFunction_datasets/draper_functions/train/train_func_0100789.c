record_one_stack_ref (rtx insn, rtx *ref, struct csa_reflist *next_reflist)
{
  struct csa_reflist *ml;

  ml = XNEW (struct csa_reflist);

  if (REG_P (*ref) || XEXP (*ref, 0) == stack_pointer_rtx)
    ml->sp_offset = 0;
  else
    ml->sp_offset = INTVAL (XEXP (XEXP (*ref, 0), 1));

  ml->insn = insn;
  ml->ref = ref;
  ml->next = next_reflist;

  return ml;
}
