void Item_maxmin_subselect::no_rows_in_result()
{


  if (parsing_place != SELECT_LIST || const_item())
    return;
  value= Item_cache::get_cache(thd, new (thd->mem_root) Item_null(thd));
  null_value= 0;
  was_values= 0;
  make_const();
}
