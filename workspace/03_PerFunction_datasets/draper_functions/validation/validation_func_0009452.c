output_sumti_tail(TreeNode *x, WhatToShow what)
{
  int n, i;
  struct nonterm *y;
  TreeNode *c1;

  y = &x->data.nonterm;

  c1 = y->children[0];
  n = y->nchildren;
  if (c1->data.nonterm.type == SUMTI_6) {
    switch (what) {
      case SHOW_LOJBAN:
      case SHOW_LOJBAN_AND_INDICATORS:
      case SHOW_BOTH:
        output_internal(c1, SHOW_LOJBAN);
        (drv->translation)(" ");

        break;
      default:
        break;
    }
    for (i=1; i<n; i++) {
      output_internal(y->children[i], what);
    }
    switch (what) {
      case SHOW_ENGLISH:
      case SHOW_BOTH:
        (drv->translation)("[of]");
        output_internal(c1, SHOW_ENGLISH);
        break;
      default:
        break;
    }
  } else {
    for (i=0; i<n; i++) {
      output_internal(y->children[i], what);
    }
  }
}
