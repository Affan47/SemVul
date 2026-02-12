static void clear_tables(JOIN *join, table_map *cleared_tables)
{


  for (uint i= 0 ; i < join->table_count ; i++)
  {
    TABLE *table= join->table[i];

    if (table->null_row)
      continue;
    if (!(table->map & join->const_table_map) || cleared_tables)
    {
      if (cleared_tables)
      {
        (*cleared_tables)|= (((table_map) 1) << i);
        if (table->s->null_bytes)
        {


          memcpy(table->record[1], table->null_flags, table->s->null_bytes);
        }
      }
      mark_as_null_row(table);
    }
  }
}
