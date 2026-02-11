g_vfs_backend_finalize (GObject *object)
{
  GVfsBackend *backend;

  backend = G_VFS_BACKEND (object);

  g_vfs_daemon_unregister_path (backend->priv->daemon, backend->priv->object_path);
  g_object_unref (backend->priv->daemon);
  g_free (backend->priv->object_path);

  g_free (backend->priv->display_name);
  g_free (backend->priv->stable_name);
  g_strfreev (backend->priv->x_content_types);
  g_clear_object (&backend->priv->icon);
  g_clear_object (&backend->priv->symbolic_icon);
  g_free (backend->priv->prefered_filename_encoding);
  g_free (backend->priv->default_location);
  if (backend->priv->mount_spec)
    g_mount_spec_unref (backend->priv->mount_spec);

  if (G_OBJECT_CLASS (g_vfs_backend_parent_class)->finalize)
    (*G_OBJECT_CLASS (g_vfs_backend_parent_class)->finalize) (object);
}
