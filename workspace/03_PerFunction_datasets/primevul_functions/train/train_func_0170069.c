Field *Item::make_string_field(TABLE *table)
{
  Field *field;
  DBUG_ASSERT(collation.collation);


  if (too_big_for_varchar())
    field= new Field_blob(max_length, maybe_null, name,
                          collation.collation, TRUE);

  else if (max_length > 0 &&
      (type() != Item::TYPE_HOLDER || field_type() != MYSQL_TYPE_STRING))
    field= new Field_varstring(max_length, maybe_null, name, table->s,
                               collation.collation);
  else
    field= new Field_string(max_length, maybe_null, name,
                            collation.collation);
  if (field)
    field->init(table);
  return field;
}
