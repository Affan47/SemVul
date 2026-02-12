static void optimize_keyuse(JOIN *join, DYNAMIC_ARRAY *keyuse_array)
{
  KEYUSE *end,*keyuse= dynamic_element(keyuse_array, 0, KEYUSE*);

  for (end= keyuse+ keyuse_array->elements ; keyuse < end ; keyuse++)
  {
    table_map map;


    keyuse->ref_table_rows= ~(ha_rows) 0;
    if (keyuse->used_tables &
	(map= (keyuse->used_tables & ~join->const_table_map &
	       ~OUTER_REF_TABLE_BIT)))
    {
      uint n_tables= my_count_bits(map);
      if (n_tables == 1)
      {
        DBUG_ASSERT(!(map & PSEUDO_TABLE_BITS));
        Table_map_iterator it(map);
        int tablenr= it.next_bit();
        DBUG_ASSERT(tablenr != Table_map_iterator::BITMAP_END);
	TABLE *tmp_table=join->table[tablenr];
        if (tmp_table)
          keyuse->ref_table_rows= MY_MAX(tmp_table->file->stats.records, 100);
      }
    }


    if (keyuse->used_tables == OUTER_REF_TABLE_BIT)
      keyuse->ref_table_rows= 1;
  }
}
