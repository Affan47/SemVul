mx_application_get_actions_cb (MxApplication  *application,
                               GPtrArray     **actions,
                               GError        **error)
{
  GHashTableIter iter;
  gpointer key, value;

  MxApplicationPrivate *priv = application->priv;
  GValue string_value = { 0 };
  GValue bool_value = { 0 };

  *actions = g_ptr_array_new ();
  g_value_init (&string_value, G_TYPE_STRING);
  g_value_init (&bool_value, G_TYPE_BOOLEAN);

  g_hash_table_iter_init (&iter, priv->actions);
  while (g_hash_table_iter_next (&iter, &key, &value))
    {
      const gchar *name, *display_name;

      MxAction *action = value;
      GValueArray *value_array = g_value_array_new (3);

      name = mx_action_get_name (action);
      display_name = mx_action_get_display_name (action);
      if (!name)
        name = "";
      if (!display_name)
        display_name = name;

      g_value_set_string (&string_value, name);
      g_value_array_append (value_array, &string_value);

      g_value_set_string (&string_value, display_name);
      g_value_array_append (value_array, &string_value);

      g_value_set_boolean (&bool_value, mx_action_get_active (action));
      g_value_array_append (value_array, &bool_value);

      g_ptr_array_add (*actions, value_array);
    }

  g_value_unset (&string_value);
  g_value_unset (&bool_value);

  return TRUE;
}
