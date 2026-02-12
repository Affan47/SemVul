bool Item_bool_rowready_func2::fix_length_and_dec()
{
  max_length= 1;


  if (!args[0] || !args[1])
    return FALSE;
  return setup_args_and_comparator(current_thd, &cmp);
}
