gfs_linear_problem_destroy (GfsLinearProblem * lp)
{
  g_return_if_fail (lp != NULL);

  gts_object_destroy (GTS_OBJECT (lp->id));
  gts_object_destroy (GTS_OBJECT (lp->neighbor));
  gts_object_destroy (GTS_OBJECT (lp->neighborw));

  g_array_free (lp->rhs, TRUE);
  g_array_free (lp->lhs, TRUE);

  int i;
  for (i = 0; i < lp->LP->len; i++)
    gfs_stencil_destroy (g_ptr_array_index (lp->LP, i));

  g_ptr_array_free (lp->LP, TRUE);
}
