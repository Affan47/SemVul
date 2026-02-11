gtv_unwire_plugins_video (gtk_video_private_t *priv)
{
  GList *item;
  xine_post_wire_video_port (xine_get_video_source (priv->stream),
			     priv->video_port);
  item = g_list_last (priv->post_video.list);
  while (item)
  {
    xine_post_wire (NULL, gtv_post_input_video (item->data));
    item = g_list_previous (item);
  }
}
