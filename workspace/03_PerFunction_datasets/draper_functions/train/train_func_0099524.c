print_idecode_lookups (lf *file, gen_entry *table, cache_entry *cache_rules)
{
  int depth;


  gen_entry_traverse_tree (file, table, 1, idecode_declare_if_switch,
			   NULL, NULL, NULL);


  for (depth = gen_entry_depth (table); depth > 0; depth--)
    {
      gen_entry_traverse_tree (file, table,
			       1 - depth,
			       print_idecode_table_start,
			       print_idecode_table_leaf,
			       print_idecode_table_end, NULL);
    }


  gen_entry_traverse_tree (file, table, 1, idecode_expand_if_switch,
			   NULL, NULL, NULL);
}
