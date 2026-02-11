gvdb_table_get_value (GvdbTable   *table,
                      const gchar *key)
{
  DConfMockGvdbItem *item;

  item = g_hash_table_lookup (table->table, key);

  return (item && item->value) ? g_variant_ref (item->value) : NULL;
}
