bool Item_func_between::fix_length_and_dec()
{
  max_length= 1;


  if (!args[0] || !args[1] || !args[2])
    return TRUE;
  if (m_comparator.aggregate_for_comparison(Item_func_between::func_name(),
                                            args, 3, false))
  {
    DBUG_ASSERT(current_thd->is_error());
    return TRUE;
  }

  return m_comparator.type_handler()->
    Item_func_between_fix_length_and_dec(this);
}
