find_network_by_address (const gchar *id,
                         TpawIrcNetwork *network,
                         const gchar *address)
{
  GSList *servers, *l;
  gboolean found = FALSE;

  if (network->dropped)
    return FALSE;

  servers = tpaw_irc_network_get_servers (network);

  for (l = servers; l != NULL && !found; l = g_slist_next (l))
    {
      TpawIrcServer *server = l->data;
      gchar *_address;

      g_object_get (server, "address", &_address, NULL);
      found = (_address != NULL && g_strcmp0 (address, _address) == 0);

      g_free (_address);
    }

  g_slist_foreach (servers, (GFunc) g_object_unref, NULL);
  g_slist_free (servers);

  return found;
}
