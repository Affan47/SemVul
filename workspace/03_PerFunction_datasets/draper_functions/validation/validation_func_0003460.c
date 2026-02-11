monitor_switch_active_cb (GObject    *object,
                          GParamSpec *pspec,
                          gpointer    data)
{
  CcDisplayPanel *self = data;
  gboolean value;

  if (!self->priv->current_output)
    return;

  value = gtk_switch_get_active (GTK_SWITCH (object));

  if (value)
    {
      gnome_rr_output_info_set_active (self->priv->current_output, TRUE);
      select_resolution_for_current_output (self);
    }
  else
    {
      gnome_rr_output_info_set_active (self->priv->current_output, FALSE);
      gnome_rr_config_ensure_primary (self->priv->current_configuration);
    }

  rebuild_gui (self);
  foo_scroll_area_invalidate (FOO_SCROLL_AREA (self->priv->area));
}
