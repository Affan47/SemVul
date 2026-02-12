onig_get_callout_start_func(regex_t* reg, int callout_num)
{

  CalloutListEntry* e;

  e = onig_reg_callout_list_at(reg, callout_num);
  return e->start_func;
}
