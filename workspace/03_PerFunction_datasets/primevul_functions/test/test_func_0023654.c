Item *in_longlong::create_item(THD *thd)
{


  return new (thd->mem_root) Item_int(thd, (longlong)0);
}
