resolve_fstab_device_diskbyid (guestfs_h *g, const char *part,
                               char **device_ret)
{
  int nr_devices;
  char *device;


  nr_devices = guestfs_nr_devices (g);
  if (nr_devices == -1)
    return -1;


  if (nr_devices != 1)
    return 0;


  device = safe_asprintf (g, "/dev/sda%s", part);
  if (!is_partition (g, device)) {
    free (device);
    return 0;
  }

  *device_ret = device;
  return 0;
}
