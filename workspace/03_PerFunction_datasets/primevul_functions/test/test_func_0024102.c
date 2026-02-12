static void clear_tables(JOIN *join)
{


  for (uint i= 0 ; i < join->table_count ; i++)
  {
    if (!(join->table[i]->map & join->const_table_map))
      mark_as_null_row(join->table[i]);
  }
}
