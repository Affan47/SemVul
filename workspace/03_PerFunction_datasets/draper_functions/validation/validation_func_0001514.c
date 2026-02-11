do_SUBST_MODE (rtx *into, enum machine_mode newval)
{
  struct undo *buf;
  enum machine_mode oldval = GET_MODE (*into);

  if (oldval == newval)
    return;

  if (undobuf.frees)
    buf = undobuf.frees, undobuf.frees = buf->next;
  else
    buf = XNEW (struct undo);

  buf->kind = UNDO_MODE;
  buf->where.r = into;
  buf->old_contents.m = oldval;
  adjust_reg_mode (*into, newval);

  buf->next = undobuf.undos, undobuf.undos = buf;
}
