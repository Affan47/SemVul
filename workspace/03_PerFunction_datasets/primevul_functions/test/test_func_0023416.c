Item *Item_func_case_simple::find_item()
{

  uint idx;
  if (!Predicant_to_list_comparator::cmp(this, &idx, NULL))
    return args[idx + when_count()];
  Item **pos= Item_func_case_simple::else_expr_addr();
  return pos ? pos[0] : 0;
}
