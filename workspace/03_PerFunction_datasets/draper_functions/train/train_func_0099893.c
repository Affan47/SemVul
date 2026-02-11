tp_intset_union_update (TpIntset *self,
    const TpIntset *other)
{
  gpointer key, value;
  GHashTableIter iter;

  g_hash_table_iter_init (&iter, (GHashTable *) other->table);

  while (g_hash_table_iter_next (&iter, &key, &value))
    {
      gsize v = GPOINTER_TO_SIZE (value);

      intset_update_largest_ever (self, key);
      v |= GPOINTER_TO_SIZE (g_hash_table_lookup (self->table, key));
      g_hash_table_insert (self->table, key, GSIZE_TO_POINTER (v));
    }
}
