Item *Item_func_not::neg_transformer(THD *thd)
{
  return args[0];
}
