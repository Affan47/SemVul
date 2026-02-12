void Item_in_optimizer::fix_after_pullout(st_select_lex *new_parent,
                                          Item **ref, bool merge)
{
  DBUG_ASSERT(fixed);

  Item_bool_func::fix_after_pullout(new_parent, ref, merge);


  eval_not_null_tables(NULL);
}
