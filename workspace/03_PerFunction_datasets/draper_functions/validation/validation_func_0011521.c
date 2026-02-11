fill_info (GFileInfo *info, GVfsAfpVolumeData *vol_data, GVfsBackendAfpBrowse *afp_backend)
{
  GIcon *icon;
  GMountSpec *mount_spec;
  char *uri;

  g_file_info_set_name (info, vol_data->name);
  g_file_info_set_display_name (info, vol_data->name);
  g_file_info_set_edit_name (info, vol_data->name);
  g_file_info_set_attribute_boolean (info, G_FILE_ATTRIBUTE_STANDARD_IS_VIRTUAL, TRUE);
  g_file_info_set_content_type (info, "inode/directory");
  g_file_info_set_file_type (info, G_FILE_TYPE_MOUNTABLE);

  g_file_info_set_attribute_boolean (info, "afp::volume-password-protected", (vol_data->flags & 0x01));

  icon = g_themed_icon_new_with_default_fallbacks ("folder-remote-afp");
  g_file_info_set_icon (info, icon);
  g_object_unref (icon);

  icon = g_themed_icon_new_with_default_fallbacks ("folder-remote-symbolic");
  g_file_info_set_symbolic_icon (info, icon);
  g_object_unref (icon);

  mount_spec = g_mount_spec_new ("afp-volume");
  g_mount_spec_set (mount_spec, "host",
                    g_network_address_get_hostname (G_NETWORK_ADDRESS (afp_backend->addr)));
  g_mount_spec_set (mount_spec, "volume", vol_data->name);
  g_mount_spec_set (mount_spec, "user", afp_backend->logged_in_user);

  if (g_mount_tracker_has_mount_spec (afp_backend->mount_tracker, mount_spec))
  {
    g_file_info_set_attribute_boolean (info, G_FILE_ATTRIBUTE_MOUNTABLE_CAN_MOUNT, FALSE);
    g_file_info_set_attribute_boolean (info, G_FILE_ATTRIBUTE_MOUNTABLE_CAN_UNMOUNT, TRUE);
  }
  else
  {
    g_file_info_set_attribute_boolean (info, G_FILE_ATTRIBUTE_MOUNTABLE_CAN_MOUNT, TRUE);
    g_file_info_set_attribute_boolean(info, G_FILE_ATTRIBUTE_MOUNTABLE_CAN_UNMOUNT, FALSE);
  }
  g_mount_spec_unref (mount_spec);

  uri = g_strdup_printf ("afp://%s/%s",
                         g_network_address_get_hostname (G_NETWORK_ADDRESS (afp_backend->addr)),
                         vol_data->name);
  g_file_info_set_attribute_string (info, G_FILE_ATTRIBUTE_STANDARD_TARGET_URI,
                                    uri);
  g_free (uri);
}
