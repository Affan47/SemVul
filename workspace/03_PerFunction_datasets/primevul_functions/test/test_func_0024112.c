Field *Item::create_tmp_field(bool group, TABLE *table, uint convert_int_length)
{
  Field *UNINIT_VAR(new_field);
  MEM_ROOT *mem_root= table->in_use->mem_root;

  switch (cmp_type()) {
  case REAL_RESULT:
    new_field= new (mem_root)
      Field_double(max_length, maybe_null, name, decimals, TRUE);
    break;
  case INT_RESULT:


    if (max_char_length() > convert_int_length)
      new_field= new (mem_root)
        Field_longlong(max_char_length(), maybe_null, name, unsigned_flag);
    else
      new_field= new (mem_root)
        Field_long(max_char_length(), maybe_null, name, unsigned_flag);
    break;
  case TIME_RESULT:
    new_field= tmp_table_field_from_field_type(table, true, false);
    break;
  case STRING_RESULT:
    DBUG_ASSERT(collation.collation);


    if (field_type() == MYSQL_TYPE_GEOMETRY)
      new_field= tmp_table_field_from_field_type(table, true, false);
    else
      new_field= make_string_field(table);
    new_field->set_derivation(collation.derivation, collation.repertoire);
    break;
  case DECIMAL_RESULT:
    new_field= Field_new_decimal::create_from_item(mem_root, this);
    break;
  case ROW_RESULT:

    DBUG_ASSERT(0);
    new_field= 0;
    break;
  }
  if (new_field)
    new_field->init(table);
  return new_field;
}
