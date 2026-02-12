Item *Item_func_ne::negated_item(THD *thd)
{
  return new (thd->mem_root) Item_func_eq(thd, args[0], args[1]);
}
