expand_automata (void)
{
  int i;

  description = XCREATENODEVAR (struct description,
				sizeof (struct description)

				+ sizeof (decl_t) * (VEC_length (decl_t, decls) + 1));
  description->decls_num = VEC_length (decl_t, decls);
  description->normal_decls_num = description->decls_num;
  description->query_units_num = 0;
  for (i = 0; i < description->decls_num; i++)
    {
      description->decls [i] = VEC_index (decl_t, decls, i);
      if (description->decls [i]->mode == dm_unit
	  && DECL_UNIT (description->decls [i])->query_p)
        DECL_UNIT (description->decls [i])->query_num
	  = description->query_units_num++;
    }
  all_time = create_ticker ();
  check_time = create_ticker ();
  if (progress_flag)
    fprintf (stderr, "Check description...");
  check_all_description ();
  if (progress_flag)
    fprintf (stderr, "done\n");
  ticker_off (&check_time);
  generation_time = create_ticker ();
  if (!have_error)
    {
      transform_insn_regexps ();
      check_unit_distributions_to_automata ();
    }
  if (!have_error)
    {
      generate ();
      check_automata_insn_issues ();
    }
  if (!have_error)
    {
      form_important_insn_automata_lists ();
    }
  ticker_off (&generation_time);
}
