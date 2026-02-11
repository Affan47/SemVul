g_mount_tracker_finalize (GObject *object)
{
  GMountTracker *tracker;

  tracker = G_MOUNT_TRACKER (object);

  g_mutex_clear (&tracker->lock);

  g_list_free_full (tracker->mounts, (GDestroyNotify)g_mount_info_unref);

  g_clear_object (&tracker->proxy);
  g_clear_object (&tracker->connection);

  if (G_OBJECT_CLASS (g_mount_tracker_parent_class)->finalize)
    (*G_OBJECT_CLASS (g_mount_tracker_parent_class)->finalize) (object);
}
