p_gap_message(const char *msg)
{
  static GapArrButtonArg  l_argv[1];
  int               l_argc;

  l_argv[0].but_txt  = GTK_STOCK_OK;
  l_argv[0].but_val  = 0;
  l_argc             = 1;

  if(msg)
  {
    if(*msg)
    {
       if(gap_debug) printf("%s\n", msg);
       gap_arr_buttons_dialog  (_("GAP Message"), msg, l_argc, l_argv, -1);
    }
  }
}
