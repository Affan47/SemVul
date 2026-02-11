emit_group_load (rtx dst, rtx src, tree type, int ssize)
{
  rtx *tmps;
  int i;

  tmps = XALLOCAVEC (rtx, XVECLEN (dst, 0));
  emit_group_load_1 (tmps, dst, src, type, ssize);


  for (i = 0; i < XVECLEN (dst, 0); i++)
    {
      rtx d = XEXP (XVECEXP (dst, 0, i), 0);
      if (d == NULL)
	continue;
      emit_move_insn (d, tmps[i]);
    }
}
