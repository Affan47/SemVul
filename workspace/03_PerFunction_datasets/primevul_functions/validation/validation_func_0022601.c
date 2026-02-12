Item_func_between::add_key_fields(JOIN *join, KEY_FIELD **key_fields,
                                  uint *and_level, table_map usable_tables,
                                  SARGABLE_PARAM **sargables)
{


  Item_field *field_item;
  bool equal_func= false;
  uint num_values= 2;

  bool binary_cmp= (args[0]->real_item()->type() == Item::FIELD_ITEM)
        ? ((Item_field*) args[0]->real_item())->field->binary()
        : true;


  if (!negated && args[1]->eq(args[2], binary_cmp))
  {
    equal_func= true;
    num_values= 1;
  }


  if (is_local_field(args[0]))
  {
    field_item= (Item_field *) (args[0]->real_item());
    add_key_equal_fields(join, key_fields, *and_level, this,
                         field_item, equal_func, &args[1],
                         num_values, usable_tables, sargables);
  }


  for (uint i= 1; i <= num_values; i++)
  {
    if (is_local_field(args[i]))
    {
      field_item= (Item_field *) (args[i]->real_item());
      add_key_equal_fields(join, key_fields, *and_level, this,
                           field_item, equal_func, args,
                           1, usable_tables, sargables);
    }
  }
}
