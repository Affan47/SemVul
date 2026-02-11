_get_tracks_cb (RestProxyCall *call,
                const GError  *error,
                GObject       *weak_object,
                gpointer       user_data)
{
  SwLastfmItemView *item_view = SW_LASTFM_ITEM_VIEW (weak_object);
  SwLastfmItemViewPrivate *priv = GET_PRIVATE (item_view);
  RestXmlNode *user_node = user_data;
  RestXmlNode *root, *track_node;
  SwService *service;


  sw_call_list_remove (priv->calls, call);

  if (error) {
    g_message (G_STRLOC ": error from Last.fm: %s", error->message);
    g_object_unref (call);
    return;
  }

  SW_DEBUG (LASTFM, "Got results for getTracks call");

  root = node_from_call (call);
  g_object_unref (call);
  if (!root)
    return;

  SW_DEBUG (LASTFM, "Parsed results for getTracks call");


  service = sw_item_view_get_service (SW_ITEM_VIEW (item_view));


  for (track_node = rest_xml_node_find (root, "track"); track_node; track_node = track_node->next)
  {
    SwItem *item;

    item = make_item (item_view, service, user_node, track_node);

    if (!sw_service_is_uid_banned (service,
                                   sw_item_get (item, "id")))
    {
      sw_set_add (priv->set, (GObject *)item);
    }

    g_object_unref (item);
  }

  rest_xml_node_unref (root);
  rest_xml_node_unref (user_node);

  _update_if_done (item_view);
}
