debug_tree_chain (tree t)
{
  struct pointer_set_t *seen = pointer_set_create ();

  while (t)
    {
      print_generic_expr (stderr, t, TDF_VOPS|TDF_MEMSYMS|TDF_UID);
      fprintf (stderr, " ");
      t = TREE_CHAIN (t);
      if (pointer_set_insert (seen, t))
	{
	  fprintf (stderr, "... [cycled back to ");
	  print_generic_expr (stderr, t, TDF_VOPS|TDF_MEMSYMS|TDF_UID);
	  fprintf (stderr, "]");
	  break;
	}
    }
  fprintf (stderr, "\n");

  pointer_set_destroy (seen);
}
