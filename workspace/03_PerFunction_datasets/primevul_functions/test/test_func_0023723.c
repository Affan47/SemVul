bool Predicant_to_list_comparator::add_value_skip_null(const char *funcname,
                                                       Item_args *args,
                                                       uint value_index,
                                                       bool *nulls_found)
{


  if (args->arguments()[value_index]->real_item()->type() == Item::NULL_ITEM)
  {
    *nulls_found= true;
    return false;
  }
  return add_value(funcname, args, value_index);
}
