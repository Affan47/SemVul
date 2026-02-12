Item_func_ne::add_key_fields(JOIN *join, KEY_FIELD **key_fields,
                             uint *and_level, table_map usable_tables,
                             SARGABLE_PARAM **sargables)
{
  if (!(used_tables() & OUTER_REF_TABLE_BIT))
  {


    if (is_local_field(args[0]) && !is_local_field(args[1]))
      add_key_equal_fields(join, key_fields, *and_level, this,
                           (Item_field*) (args[0]->real_item()), false,
                           &args[1], 1, usable_tables, sargables);


    if (is_local_field(args[1]) && !is_local_field(args[0]))
      add_key_equal_fields(join, key_fields, *and_level, this,
                           (Item_field*) (args[1]->real_item()), false,
                           &args[0], 1, usable_tables, sargables);
  }
}
