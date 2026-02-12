add_key_field(JOIN *join,
              KEY_FIELD **key_fields,uint and_level, Item_bool_func *cond,
              Field *field, bool eq_func, Item **value, uint num_values,
              table_map usable_tables, SARGABLE_PARAM **sargables,
              uint row_col_no= 0)
{
  uint optimize= 0;
  if (eq_func &&
      ((join->is_allowed_hash_join_access() &&
        field->hash_join_is_possible() &&
        !(field->table->pos_in_table_list->is_materialized_derived() &&
          field->table->is_created())) ||
       (field->table->pos_in_table_list->is_materialized_derived() &&
        !field->table->is_created() && !(field->flags & BLOB_FLAG))))
  {
    optimize= KEY_OPTIMIZE_EQ;
  }
  else if (!(field->flags & PART_KEY_FLAG))
  {

    if (eq_func && (*value)->type() == Item::NULL_ITEM &&
        field->table->maybe_null && !field->null_ptr)
    {
      optimize= KEY_OPTIMIZE_EXISTS;
      DBUG_ASSERT(num_values == 1);
    }
  }
  if (optimize != KEY_OPTIMIZE_EXISTS)
  {
    table_map used_tables=0;
    bool optimizable=0;
    for (uint i=0; i<num_values; i++)
    {
      Item *curr_val;
      if (row_col_no && value[i]->real_item()->type() == Item::ROW_ITEM)
      {
        Item_row *value_tuple= (Item_row *) (value[i]->real_item());
        curr_val= value_tuple->element_index(row_col_no - 1);
      }
      else
        curr_val= value[i];
      table_map value_used_tables= curr_val->used_tables();
      used_tables|= value_used_tables;
      if (!(value_used_tables & (field->table->map | RAND_TABLE_BIT)))
        optimizable=1;
    }
    if (!optimizable)
      return;
    if (!(usable_tables & field->table->map))
    {
      if (!eq_func || (*value)->type() != Item::NULL_ITEM ||
          !field->table->maybe_null || field->null_ptr)
	return;
      optimize= KEY_OPTIMIZE_EXISTS;
    }
    else
    {
      JOIN_TAB *stat=field->table->reginfo.join_tab;
      key_map possible_keys=field->get_possible_keys();
      possible_keys.intersect(field->table->keys_in_use_for_query);
      stat[0].keys.merge(possible_keys);


      if (field->flags & PART_KEY_FLAG)
        stat[0].key_dependent|=used_tables;

      bool is_const=1;
      for (uint i=0; i<num_values; i++)
      {
        Item *curr_val;
        if (row_col_no && value[i]->real_item()->type() == Item::ROW_ITEM)
	{
          Item_row *value_tuple= (Item_row *) (value[i]->real_item());
          curr_val= value_tuple->element_index(row_col_no - 1);
        }
        else
          curr_val= value[i];
        if (!(is_const&= curr_val->const_item()))
          break;
      }
      if (is_const)
      {
        stat[0].const_keys.merge(possible_keys);
        bitmap_set_bit(&field->table->cond_set, field->field_index);
      }
      else if (!eq_func)
      {


        (*sargables)--;
        (*sargables)->field= field;
        (*sargables)->arg_value= value;
        (*sargables)->num_values= num_values;
      }
      if (!eq_func)
        return;
    }
  }


  DBUG_ASSERT(eq_func);

  (*key_fields)->field=		field;
  (*key_fields)->eq_func=	eq_func;
  (*key_fields)->val=		*value;
  (*key_fields)->cond=          cond;
  (*key_fields)->level=         and_level;
  (*key_fields)->optimize=      optimize;


  {
    Item *real= (*value)->real_item();
    if (((cond->functype() == Item_func::EQ_FUNC) ||
         (cond->functype() == Item_func::MULT_EQUAL_FUNC)) &&
        (real->type() == Item::FIELD_ITEM) &&
        ((Item_field*)real)->field->maybe_null())
      (*key_fields)->null_rejecting= true;
    else
      (*key_fields)->null_rejecting= false;
  }
  (*key_fields)->cond_guard= NULL;

  (*key_fields)->sj_pred_no= get_semi_join_select_list_index(field);
  (*key_fields)++;
}
