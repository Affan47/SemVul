Cached_item_field(THD *thd, Field *arg_field): field(arg_field)
  {
    field= arg_field;

    buff= (uchar*) thd_calloc(thd, length= field->pack_length());
  }
