Item_param::Item_param(uint pos_in_query_arg) :
  state(NO_VALUE),
  item_result_type(STRING_RESULT),

  item_type(PARAM_ITEM),
  param_type(MYSQL_TYPE_VARCHAR),
  pos_in_query(pos_in_query_arg),
  set_param_func(default_set_param_func),
  limit_clause_param(FALSE),
  m_out_param_info(NULL)
{
  name= (char*) "?";


  maybe_null= 1;
  cnvitem= new Item_string("", 0, &my_charset_bin, DERIVATION_COERCIBLE);
  cnvstr.set(cnvbuf, sizeof(cnvbuf), &my_charset_bin);
}
