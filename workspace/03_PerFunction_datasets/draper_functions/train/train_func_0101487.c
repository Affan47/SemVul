Lookup_In_Dico_Var(char *name)
{
  int i;
  Bool named;

  if (name[0] != '_' || name[1] != '\0')
    {
      named = TRUE;
      for (i = 0;
	   i < parse_nb_var && strcmp(name, parse_dico_var[i].name) != 0;
	   i++)
	;
    }
  else
    {
      named = FALSE;
      i = parse_nb_var;
    }

  if (i == parse_nb_var)
    {
      if (parse_nb_var >= MAX_VAR_IN_TERM)
	Parse_Error("too many variables in a term");

      strcpy(parse_dico_var[parse_nb_var].name, name);
      parse_dico_var[parse_nb_var].word = NOT_A_WAM_WORD;
      parse_dico_var[parse_nb_var].named = named;
      parse_dico_var[parse_nb_var].nb_of_uses = 0;
      parse_nb_var++;
    }

  return i;
}
