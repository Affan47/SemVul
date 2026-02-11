finish_insns (void)
{
  unsigned i;


  for (i = 0; i < s_i_d.length (); i++)
    {
      sel_insn_data_def *sid_entry = &s_i_d[i];

      if (sid_entry->live)
        return_regset_to_pool (sid_entry->live);
      if (sid_entry->analyzed_deps)
	{
	  BITMAP_FREE (sid_entry->analyzed_deps);
	  BITMAP_FREE (sid_entry->found_deps);
          htab_delete (sid_entry->transformed_insns);
	  free_deps (&sid_entry->deps_context);
	}
      if (EXPR_VINSN (&sid_entry->expr))
        {
          clear_expr (&sid_entry->expr);


          CANT_MOVE_BY_LUID (i) = 0;
        }
    }

  s_i_d.release ();
}
