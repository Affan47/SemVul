twitter_item_view_start (SwItemView *item_view)
{
  SwTwitterItemViewPrivate *priv = GET_PRIVATE (item_view);

  if (priv->timeout_id)
  {
    g_warning (G_STRLOC ": View already started.");
  } else {
    SW_DEBUG (TWITTER, G_STRLOC ": Setting up the timeout");
    priv->timeout_id = g_timeout_add_seconds (UPDATE_TIMEOUT,
                                              (GSourceFunc)_update_timeout_cb,
                                              item_view);

    _load_from_cache ((SwTwitterItemView *)item_view);
    _get_status_updates ((SwTwitterItemView *)item_view);
  }
}
