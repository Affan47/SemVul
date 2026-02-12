Item_equal::add_key_fields(JOIN *join, KEY_FIELD **key_fields,
                           uint *and_level, table_map usable_tables,
                           SARGABLE_PARAM **sargables)
{
  Item *const_item2= get_const();
  Item_equal_fields_iterator it(*this);
  if (const_item2)
  {


    while (it++)
    {
      Field *equal_field= it.get_curr_field();
      add_key_field(join, key_fields, *and_level, this, equal_field,
                    TRUE, &const_item2, 1, usable_tables, sargables);
    }
  }
  else
  {


    Item_equal_fields_iterator fi(*this);
    while (fi++)
    {
      Field *field= fi.get_curr_field();
      Item *item;
      while ((item= it++))
      {
        Field *equal_field= it.get_curr_field();
        if (!field->eq(equal_field))
        {
          add_key_field(join, key_fields, *and_level, this, field,
                        TRUE, &item, 1, usable_tables,
                        sargables);
        }
      }
      it.rewind();
    }
  }
}
