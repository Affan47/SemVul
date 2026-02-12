bool Item_func_between::eval_not_null_tables(void *opt_arg)
{
  if (Item_func_opt_neg::eval_not_null_tables(NULL))
    return 1;


  if (pred_level && !negated)
    return 0;


  not_null_tables_cache= (args[0]->not_null_tables() |
                          (args[1]->not_null_tables() &
                           args[2]->not_null_tables()));
  return 0;
}
