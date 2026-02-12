determine_search_depth(JOIN *join)
{
  uint table_count=  join->table_count - join->const_tables;
  uint search_depth;

  uint max_tables_for_exhaustive_opt= 7;

  if (table_count <= max_tables_for_exhaustive_opt)
    search_depth= table_count+1;
  else


    search_depth= max_tables_for_exhaustive_opt;

  return search_depth;
}
