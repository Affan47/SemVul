cally_util_add_key_event_listener (AtkKeySnoopFunc  listener,
                                   gpointer         data)
{
  static guint key = 1;
  CallyKeyEventInfo *event_info = NULL;

  if (!key_listener_list)
  {
    key_listener_list = g_hash_table_new_full (NULL, NULL, NULL, g_free);

    cally_util_simulate_snooper_install ();
  }

  event_info = g_new (CallyKeyEventInfo, 1);
  event_info->listener = listener;
  event_info->func_data = data;

  g_hash_table_insert (key_listener_list, GUINT_TO_POINTER (key++), event_info);

  return key - 1;
}
