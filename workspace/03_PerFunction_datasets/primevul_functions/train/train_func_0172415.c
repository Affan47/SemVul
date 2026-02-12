static void didset_options2(void)
{

  (void)highlight_changed();


  (void)opt_strings_flags(p_cb, p_cb_values, &cb_flags, true);


  (void)set_chars_option(&p_fcs);


  (void)set_chars_option(&p_lcs);


  check_opt_wim();
}
