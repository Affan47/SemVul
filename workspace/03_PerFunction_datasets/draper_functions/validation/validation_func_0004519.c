remove_from_both_dependence_lists (rtx insn, rtx *listp, rtx *exprp)
{
  int removed = 0;

  while (*listp)
    {
      if (XEXP (*listp, 0) == insn)
        {
          remove_free_INSN_LIST_node (listp);
          remove_free_EXPR_LIST_node (exprp);
          removed++;
          continue;
        }

      listp = &XEXP (*listp, 1);
      exprp = &XEXP (*exprp, 1);
    }

  return removed;
}
