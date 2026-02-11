got_xdg_volume_info_cb (GObject      *source_object,
                        GAsyncResult *res,
                        gpointer      user_data)
{
  GVfsUDisks2Mount *mount = GVFS_UDISKS2_MOUNT (user_data);
  mount->xdg_volume_info_icon = g_vfs_mount_info_query_xdg_volume_info_finish (G_FILE (source_object),
                                                                               res,
                                                                               &(mount->xdg_volume_info_name),
                                                                               NULL);
  if (update_mount (mount))
    emit_changed (mount);
  g_object_unref (mount);
}
