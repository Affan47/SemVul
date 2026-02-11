do_power_off (GduWindow *window)
{
  UDisksObject *object;
  GList *objects = NULL;
  GList *siblings, *l;
  UDisksDrive *drive;
  const gchar *heading;
  const gchar *message;

  object = window->current_object;
  drive = udisks_object_peek_drive (object);
  objects = g_list_append (NULL, object);


  siblings = udisks_client_get_drive_siblings (window->client, drive);
  for (l = siblings; l != NULL; l = l->next)
    {
      UDisksDrive *sibling = UDISKS_DRIVE (l->data);
      UDisksObject *sibling_object = (UDisksObject *) g_dbus_interface_get_object (G_DBUS_INTERFACE (sibling));
      if (sibling_object != NULL)
        objects = g_list_append (objects, sibling_object);
    }

  if (siblings != NULL)
    {

      heading = _("Are you sure you want to power off the drives?");

      message = _("This operation will prepare the system for the following drives to be powered down and removed.");
      if (!gdu_utils_show_confirmation (GTK_WINDOW (window),
                                        heading,
                                        message,
                                        _("_Power Off"),
                                        NULL, NULL,
                                        window->client, objects))
        goto out;
    }

  gdu_window_ensure_unused_list (window,
                                 objects,
                                 (GAsyncReadyCallback) power_off_ensure_unused_cb,
                                 NULL,
                                 g_object_ref (object));
 out:
  g_list_free_full (siblings, g_object_unref);
  g_list_free (objects);
}
