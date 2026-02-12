Item_field::create_tmp_field_from_item_field(TABLE *new_table,
                                             Item_ref *orig_item,
                                             const Tmp_field_param *param)
{
  DBUG_ASSERT(!is_result_field());
  Field *result;
  LEX_CSTRING *new_name= (orig_item ? &orig_item->name :
                          !param->modify_item() ? &name :
                          &field->field_name);


  if (((maybe_null && in_rollup) ||
      (new_table->in_use->create_tmp_table_for_derived &&
       orig_item && orig_item->maybe_null)) &&
      !field->maybe_null())
  {


    Record_addr rec(orig_item ? orig_item->maybe_null : maybe_null);
    const Type_handler *handler= type_handler()->
                                   type_handler_for_tmp_table(this);
    result= handler->make_and_init_table_field(new_name,
                                               rec, *this, new_table);
  }
  else if (param->table_cant_handle_bit_fields() &&
           field->type() == MYSQL_TYPE_BIT)
  {
    const Type_handler *handler= type_handler_long_or_longlong();
    result= handler->make_and_init_table_field(new_name,
                                               Record_addr(maybe_null),
                                               *this, new_table);
  }
  else
  {
    bool tmp_maybe_null= param->modify_item() ? maybe_null :
                                                field->maybe_null();
    result= field->create_tmp_field(new_table->in_use->mem_root, new_table,
                                    tmp_maybe_null);
    if (result && ! param->modify_item())
      result->field_name= *new_name;
  }
  if (result && param->modify_item())
    result_field= result;
  return result;
}
