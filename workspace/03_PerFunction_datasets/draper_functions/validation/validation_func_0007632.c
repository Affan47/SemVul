ftt_cell_traverse_new (FttCell * root,
					 FttTraverseType order,
					 FttTraverseFlags flags,
					 gint max_depth)
{
  FttCellTraverse * t;
  GPtrArray * a;

  g_return_val_if_fail (root != NULL, NULL);

  a = g_ptr_array_new ();
  ftt_cell_traverse (root, order, flags, max_depth,
		     (FttCellTraverseFunc) cell_traverse_add, a);
  g_ptr_array_add (a, NULL);
  t = g_malloc (sizeof (FttCellTraverse));
  t->current = t->cells = (FttCell **) a->pdata;
  g_ptr_array_free (a, FALSE);
  return t;
}
