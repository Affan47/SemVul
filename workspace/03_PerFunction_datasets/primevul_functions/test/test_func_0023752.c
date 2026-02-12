Item *Item_cond_or::neg_transformer(THD *thd)

{
  neg_arguments(thd);
  Item *item= new (thd->mem_root) Item_cond_and(thd, list);
  return item;
}
