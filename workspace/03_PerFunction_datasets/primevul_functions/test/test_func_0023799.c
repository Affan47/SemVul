Type_handler_hybrid_field_type::aggregate_for_comparison(const char *funcname,
                                                         Item **items,
                                                         uint nitems,
                                                         bool int_uint_as_dec)
{
  uint unsigned_count= items[0]->unsigned_flag;


  set_handler(items[0]->type_handler()->type_handler_for_comparison());
  for (uint i= 1 ; i < nitems ; i++)
  {
    unsigned_count+= items[i]->unsigned_flag;
    if (aggregate_for_comparison(items[i]->type_handler()->
                                 type_handler_for_comparison()))
    {


      my_error(ER_ILLEGAL_PARAMETER_DATA_TYPES2_FOR_OPERATION, MYF(0),
               i == 1 ? items[0]->type_handler()->name().ptr() :
                        type_handler()->name().ptr(),
               items[i]->type_handler()->name().ptr(),
               funcname);
      return true;
    }


    if (cmp_type() == ROW_RESULT && cmp_row_type(items[0], items[i]))
      return true;
  }


  if (int_uint_as_dec &&
      cmp_type() == INT_RESULT &&
      unsigned_count != nitems && unsigned_count != 0)
    set_handler(&type_handler_newdecimal);
  return 0;
}
