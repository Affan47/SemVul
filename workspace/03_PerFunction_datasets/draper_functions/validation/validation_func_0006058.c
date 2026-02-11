g_mount_spec_hash (gconstpointer _mount)
{
  GMountSpec *mount = (GMountSpec *) _mount;
  guint hash;
  int i;

  hash = 0;
  if (mount->mount_prefix)
    hash ^= g_str_hash (mount->mount_prefix);

  for (i = 0; i < mount->items->len; i++)
    {
      GMountSpecItem *item = &g_array_index (mount->items, GMountSpecItem, i);
      hash ^= g_str_hash (item->value);
    }

  return hash;
}
