fix_length_and_dec()
{
  int max_int_part=0;
  bool datetime_found= FALSE;
  decimals=0;
  max_length=0;
  maybe_null=0;
  cmp_type=args[0]->result_type();

  for (uint i=0 ; i < arg_count ; i++)
  {
    set_if_bigger(max_length, args[i]->max_length);
    set_if_bigger(decimals, args[i]->decimals);
    set_if_bigger(max_int_part, args[i]->decimal_int_part());
    if (args[i]->maybe_null)
      maybe_null=1;
    cmp_type=item_cmp_type(cmp_type,args[i]->result_type());
    if (args[i]->result_type() != ROW_RESULT && args[i]->is_datetime())
    {
      datetime_found= TRUE;
      if (!datetime_item || args[i]->field_type() == MYSQL_TYPE_DATETIME)
        datetime_item= args[i];
    }
  }
  if (cmp_type == STRING_RESULT)
  {
    agg_arg_charsets_for_string_result_with_comparison(collation,
                                                       args, arg_count);
    if (datetime_found)
    {
      thd= current_thd;
      compare_as_dates= TRUE;
    }
  }
  else if ((cmp_type == DECIMAL_RESULT) || (cmp_type == INT_RESULT))
  {
    collation.set_numeric();
    fix_char_length(my_decimal_precision_to_length_no_truncation(max_int_part +
                                                                 decimals,
                                                                 decimals,
                                                                 unsigned_flag));
  }
  else if (cmp_type == REAL_RESULT)
    fix_char_length(float_length(decimals));
  cached_field_type= agg_field_type(args, arg_count);
}
