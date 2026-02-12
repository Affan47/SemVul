Item* Item_equal::get_first(JOIN_TAB *context, Item *field_item)
{
  Item_equal_fields_iterator it(*this);
  Item *item;
  if (!field_item)
    return (it++);
  Field *field= ((Item_field *) (field_item->real_item()))->field;


  TABLE_LIST *emb_nest;
  if (context != NO_PARTICULAR_TAB)
    emb_nest= context->emb_sj_nest;
  else
    emb_nest= field->table->pos_in_table_list->embedding;

  if (emb_nest && emb_nest->sj_mat_info && emb_nest->sj_mat_info->is_used)
  {


    while ((item= it++))
    {
      if (item->const_item() ||
          it.get_curr_field()->table->pos_in_table_list->embedding == emb_nest)
      {


        return (item != field_item) ? item : NULL;
      }
    }
  }
  else
  {


    return equal_items.head();
  }

  DBUG_ASSERT(0);
  return NULL;
}
