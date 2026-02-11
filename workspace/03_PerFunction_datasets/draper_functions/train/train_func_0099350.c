ar_clock_stop_timer (ArClock *clock_widget)
{
  if (clock_widget->priv->update_timeout_id != 0) {
    g_source_remove (clock_widget->priv->update_timeout_id);
    clock_widget->priv->update_timeout_id = 0;
  }
}
