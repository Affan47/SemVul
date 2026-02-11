_tp_bind_connection_status_to_boolean (GBinding *binding,
    const GValue *src_value,
    GValue *dest_value,
    gpointer user_data)
{
  gboolean invert = GPOINTER_TO_UINT (user_data);
  gboolean value;

  g_return_val_if_fail (G_VALUE_HOLDS_UINT (src_value), FALSE);
  g_return_val_if_fail (G_VALUE_HOLDS_BOOLEAN (dest_value), FALSE);

  value = (g_value_get_uint (src_value) == TP_CONNECTION_STATUS_CONNECTED);

  if (invert)
    value = !value;

  g_value_set_boolean (dest_value, value);

  return TRUE;
}
