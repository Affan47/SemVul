virtual Field *create_tmp_field(bool group, TABLE *table)
  {


    return create_tmp_field(false, table, MY_INT32_NUM_DECIMAL_DIGITS - 2);
  }
