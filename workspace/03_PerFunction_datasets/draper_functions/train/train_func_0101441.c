g_proxy_volume_can_eject (GVolume *volume)
{
  GProxyVolume *proxy_volume = G_PROXY_VOLUME (volume);
  GProxyDrive *drive;
  gboolean res;

  G_LOCK (proxy_volume);
  res = FALSE;
  if (proxy_volume->drive_id != NULL && strlen (proxy_volume->drive_id) > 0)
    {
      drive = g_proxy_volume_monitor_get_drive_for_id (proxy_volume->volume_monitor,
                                                       proxy_volume->drive_id);
      if (drive != NULL)
        {
          res = g_drive_can_eject (G_DRIVE (drive));
          g_object_unref (drive);
        }
    }
  G_UNLOCK (proxy_volume);

  return res;
}
