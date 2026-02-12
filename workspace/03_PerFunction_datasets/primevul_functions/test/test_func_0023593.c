Item *Item_func_gt::negated_item(THD *thd)
{
  return new (thd->mem_root) Item_func_le(thd, args[0], args[1]);
}
