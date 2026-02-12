Field *create_tmp_field_ex(TABLE *table, Tmp_field_src *src,
                             const Tmp_field_param *param)
  {


    return tmp_table_field_from_field_type_maybe_null(table, src, param,
                                            type() == Item::NULL_ITEM);
  }
