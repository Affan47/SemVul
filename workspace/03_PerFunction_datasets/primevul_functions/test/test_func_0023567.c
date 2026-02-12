void Item_func_in::fix_after_pullout(st_select_lex *new_parent, Item **ref,
                                     bool merge)
{

  Item_func_opt_neg::fix_after_pullout(new_parent, ref, merge);

  eval_not_null_tables(NULL);
}
