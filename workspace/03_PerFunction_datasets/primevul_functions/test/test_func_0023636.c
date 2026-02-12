in_row::in_row(THD *thd, uint elements, Item * item)
{
  base= (char*) new (thd->mem_root) cmp_item_row[count= elements];
  size= sizeof(cmp_item_row);
  compare= (qsort2_cmp) cmp_row;


  used_count= elements;
  collation= 0;
}
