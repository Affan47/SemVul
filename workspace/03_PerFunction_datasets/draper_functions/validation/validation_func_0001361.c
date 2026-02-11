group_concat_key_cmp_with_distinct(void* arg, const void* key1,
                                       const void* key2)
{
  Item_func_group_concat *item_func= (Item_func_group_concat*)arg;
  TABLE *table= item_func->table;

  for (uint i= 0; i < item_func->arg_count_field; i++)
  {
    Item *item= item_func->args[i];


    if (item->const_item())
      continue;


    Field *field= item->get_tmp_table_field();

    if (!field)
      continue;

    uint offset= field->offset(field->table->record[0])-table->s->null_bytes;
    int res= field->cmp((uchar*)key1 + offset, (uchar*)key2 + offset);
    if (res)
      return res;
  }
  return 0;
}
