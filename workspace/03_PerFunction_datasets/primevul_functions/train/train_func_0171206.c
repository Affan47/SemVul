void Item_allany_subselect::no_rows_in_result()
{


  if (parsing_place != SELECT_LIST || const_item())
    return;
  value= 0;
  null_value= 0;
  was_null= 0;
  make_const();
}
