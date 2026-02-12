Field *Item_default_value::create_tmp_field_ex(TABLE *table,
                                                Tmp_field_src *src,
                                                const Tmp_field_param *param)
{
  if (field->default_value && (field->flags & BLOB_FLAG))
  {


     get_tmp_field_src(src, param);
     return tmp_table_field_from_field_type(table);
  }


  src->set_field(field);
  return create_tmp_field_from_item_field(table, NULL, param);
}
