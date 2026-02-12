void set_title_defaults(void)
{
  int idx1;


  idx1 = findoption((char_u *)"title");
  if (idx1 >= 0 && !(options[idx1].flags & P_WAS_SET)) {
    options[idx1].def_val[VI_DEFAULT] = (char_u *)(intptr_t)0;
    p_title = 0;
  }
  idx1 = findoption((char_u *)"icon");
  if (idx1 >= 0 && !(options[idx1].flags & P_WAS_SET)) {
    options[idx1].def_val[VI_DEFAULT] = (char_u *)(intptr_t)0;
    p_icon = 0;
  }
}
