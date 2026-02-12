void set_init_2(void)
{
  int idx;


  set_number_default("scroll", Rows / 2);
  idx = findoption((char_u *)"scroll");
  if (idx >= 0 && !(options[idx].flags & P_WAS_SET))
    set_option_default(idx, OPT_LOCAL, p_cp);
  comp_col();


  if (!option_was_set((char_u *)"window"))
    p_window = Rows - 1;
  set_number_default("window", Rows - 1);
  parse_shape_opt(SHAPE_CURSOR);
  (void)parse_printoptions();
}
