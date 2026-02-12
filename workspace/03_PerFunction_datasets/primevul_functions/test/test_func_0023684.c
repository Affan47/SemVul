Item *Item_cond_and::neg_transformer(THD *thd)

{
  neg_arguments(thd);
  Item *item= new (thd->mem_root) Item_cond_or(thd, list);
  return item;
}
