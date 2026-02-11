same_cmp_following_p (rtx i1)
{
  rtx i2, i3;


  i2 = next_nonnote_insn (i1);
  if (i2 == NULL_RTX)
    return 0;
  i3 = next_nonnote_insn (i2);
  if (i3 == NULL_RTX)
    return 0;

  return (INSN_P (i3) && rtx_equal_p (PATTERN (i1), PATTERN (i3))
	  && any_condjump_p (i2) && onlyjump_p (i2));
}
