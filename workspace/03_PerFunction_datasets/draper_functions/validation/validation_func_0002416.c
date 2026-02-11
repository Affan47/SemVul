gen_automaton (rtx def)
{
  decl_t decl;
  char **str_automata;
  int vect_length;
  int i;

  str_automata = get_str_vect ((char *) XSTR (def, 0), &vect_length, ',',
			       FALSE);
  if (str_automata == NULL)
    fatal ("invalid string `%s' in define_automaton", XSTR (def, 0));
  for (i = 0; i < vect_length; i++)
    {
      decl = create_node (sizeof (struct decl));
      decl->mode = dm_automaton;
      decl->pos = 0;
      DECL_AUTOMATON (decl)->name = check_name (str_automata [i], decl->pos);
      VLA_PTR_ADD (decls, decl);
      num_dfa_decls++;
    }
}
