local_hooke_init(mode,mi)
int mode;
struct method_instance *mi;
{
  int flag_var;
  flag_var = lookup_global(HOOKE_FLAG_NAME);
  if ( flag_var < 0 )
  { flag_var = add_global(HOOKE_FLAG_NAME);
    globals(flag_var)->value.real = 0.0;
    globals(flag_var)->flags |=  ORDINARY_PARAM | RECALC_PARAMETER | ALWAYS_RECALC;
  }
  local_hooke_flag = (int)globals(flag_var)->value.real;
}
