gucharmap_chartable_set_codepoint_list (GucharmapChartable     *chartable,
                                        GucharmapCodepointList *codepoint_list)
{
  GucharmapChartablePrivate *priv = chartable->priv;
  GObject *object = G_OBJECT (chartable);
  GtkWidget *widget = GTK_WIDGET (chartable);

  g_object_freeze_notify (object);

  if (codepoint_list)
    g_object_ref (codepoint_list);
  if (priv->codepoint_list)
    g_object_unref (priv->codepoint_list);
  priv->codepoint_list = codepoint_list;
  priv->codepoint_list_changed = TRUE;

  priv->active_cell = 0;
  priv->page_first_cell = 0;
  if (codepoint_list)
    priv->last_cell = gucharmap_codepoint_list_get_last_index (codepoint_list);
  else
    priv->last_cell = 0;

  g_object_notify (object, "codepoint-list");
  g_object_notify (object, "active-character");

  update_scrollbar_adjustment (chartable);

  gtk_widget_queue_draw (widget);

  g_object_thaw_notify (object);
}
