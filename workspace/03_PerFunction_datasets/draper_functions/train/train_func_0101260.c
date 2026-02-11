load_statistics (void)
{
  GSList *raw_list;
  AisleriotStatistic *new_stats;
  guint64 value;

  raw_list = gconf_client_get_list (gconf_client, statistics_key,
				    GCONF_VALUE_STRING, NULL);

  while (raw_list) {
    new_stats = g_hash_table_lookup (stats, raw_list->data);

    if (!new_stats) {
      new_stats = g_new (AisleriotStatistic, 1);
      new_stats->wins = 0;
      new_stats->total = 0;
      new_stats->best = 0;
      new_stats->worst = 0;
      g_hash_table_insert (stats, raw_list->data, new_stats);
    } else {
      g_free (raw_list->data);
    }

    raw_list = g_slist_delete_link (raw_list, raw_list);

    if (!raw_list)
      break;
    new_stats->wins = g_ascii_strtoull (raw_list->data, NULL, 10);
    g_free (raw_list->data);
    raw_list = g_slist_delete_link (raw_list, raw_list);

    if (!raw_list)
      break;
    new_stats->total = g_ascii_strtoull (raw_list->data, NULL, 10);
    g_free (raw_list->data);
    raw_list = g_slist_delete_link (raw_list, raw_list);

    if (!raw_list)
      break;
    value = g_ascii_strtoull (raw_list->data, NULL, 10);

    if (value > 0 && value <= 6000) {
      new_stats->best = value;
    } else {
      new_stats->best = 0;
    }
    g_free (raw_list->data);
    raw_list = g_slist_delete_link (raw_list, raw_list);

    if (!raw_list)
      break;
    value = g_ascii_strtoull (raw_list->data, NULL, 10);

    if (value > 0 && value <= 6000) {
      new_stats->worst = value;
    } else {
      new_stats->worst = 0;
    }
    g_free (raw_list->data);
    raw_list = g_slist_delete_link (raw_list, raw_list);
  }
}
