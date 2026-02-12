resolve_fstab_device_xdev (guestfs_h *g, const char *type, const char *disk,
                           const char *part, char **device_ret)
{
  CLEANUP_FREE char *name = NULL;
  char *device;
  CLEANUP_FREE_STRING_LIST char **devices = NULL;
  size_t i, count;
  struct drive *drv;
  const char *p;


  devices = guestfs_list_devices (g);
  if (devices == NULL)
    return -1;


  name = safe_asprintf (g, "%sd%s", type, disk);
  ITER_DRIVES (g, i, drv) {
    if (drv->name && STREQ (drv->name, name)) {
      device = safe_asprintf (g, "%s%s", devices[i], part);
      if (!is_partition (g, device)) {
        free (device);
        return 0;
      }
      *device_ret = device;
      break;
    }
  }


  if (!*device_ret) {

    for (count = 0; devices[count] != NULL; count++)
      ;


    i = disk[0] - 'a';
    for (p = disk + 1; *p != '\0'; p++) {
      i += 1; i *= 26;
      i += *p - 'a';
    }


    if (i < count) {
      device = safe_asprintf (g, "%s%s", devices[i], part);
      if (!is_partition (g, device)) {
        free (device);
        return 0;
      }
      *device_ret = device;
    }
  }

  return 0;
}
