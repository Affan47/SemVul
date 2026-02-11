gen_automata_option (rtx def)
{
  if (strcmp (XSTR (def, 0), NO_MINIMIZATION_OPTION + 1) == 0)
    no_minimization_flag = 1;
  else if (strcmp (XSTR (def, 0), TIME_OPTION + 1) == 0)
    time_flag = 1;
  else if (strcmp (XSTR (def, 0), V_OPTION + 1) == 0)
    v_flag = 1;
  else if (strcmp (XSTR (def, 0), W_OPTION + 1) == 0)
    w_flag = 1;
  else if (strcmp (XSTR (def, 0), NDFA_OPTION + 1) == 0)
    ndfa_flag = 1;
  else if (strcmp (XSTR (def, 0), PROGRESS_OPTION + 1) == 0)
    progress_flag = 1;
  else
    fatal ("invalid option `%s' in automata_option", XSTR (def, 0));
}
