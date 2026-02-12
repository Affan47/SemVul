Item *Item_func_eq::negated_item(THD *thd)
{
  return new (thd->mem_root) Item_func_ne(thd, args[0], args[1]);
}
