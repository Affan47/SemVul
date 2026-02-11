store_tile (ChamplainTileCache *tile_cache,
    ChamplainTile *tile,
    const gchar *contents,
    gsize size)
{
  g_return_if_fail (CHAMPLAIN_IS_MEMORY_CACHE (tile_cache));

  ChamplainMapSource *map_source = CHAMPLAIN_MAP_SOURCE (tile_cache);
  ChamplainMapSource *next_source = champlain_map_source_get_next_source (map_source);
  ChamplainMemoryCache *memory_cache = CHAMPLAIN_MEMORY_CACHE (tile_cache);
  ChamplainMemoryCachePrivate *priv = memory_cache->priv;
  GList *link;
  gchar *key;

  key = generate_queue_key (memory_cache, tile);
  link = g_hash_table_lookup (priv->hash_table, key);
  if (link)
    {
      move_queue_member_to_head (priv->queue, link);
      g_free (key);
    }
  else
    {
      QueueMember *member;

      if (priv->queue->length >= priv->size_limit)
        {
          member = g_queue_pop_tail (priv->queue);
          g_hash_table_remove (priv->hash_table, member->key);
          delete_queue_member (member, NULL);
        }

      member = g_slice_new (QueueMember);
      member->key = key;
      member->data = g_memdup (contents, size);
      member->size = size;

      g_queue_push_head (priv->queue, member);
      g_hash_table_insert (priv->hash_table, g_strdup (key), g_queue_peek_head_link (priv->queue));
    }

  if (CHAMPLAIN_IS_TILE_CACHE (next_source))
    champlain_tile_cache_store_tile (CHAMPLAIN_TILE_CACHE (next_source), tile, contents, size);
}
