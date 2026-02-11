mx_action_new_full (const gchar *name,
                    const gchar *display_name,
                    GCallback    activated_cb,
                    gpointer     user_data)
{
  MxAction *action = g_object_new (MX_TYPE_ACTION,
                                   "display-name", display_name,
                                   NULL);

  mx_action_set_name (action, name);

  if (activated_cb)
    g_signal_connect (action, "activated", activated_cb, user_data);

  return action;
}
