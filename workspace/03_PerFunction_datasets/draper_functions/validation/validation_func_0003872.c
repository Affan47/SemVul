data_size(void)
{
  unsigned int size = 0;
  int table_pos;
  data_node_t *n;

  for (table_pos = 0; table_pos < HASH_TABLE_SIZE; table_pos++)
    for (n = data_hash_table[table_pos]; n; n = n->next)
      size++;

  return size;

}
