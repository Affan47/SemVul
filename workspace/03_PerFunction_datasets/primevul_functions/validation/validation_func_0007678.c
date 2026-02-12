resolve_fstab_device (guestfs_h *g, const char *spec, Hash_table *md_map)
{
  char *device = NULL;
  char *type, *slice, *disk, *part;
  int r;

  if (STRPREFIX (spec, "/dev/mapper/") && guestfs_exists (g, spec) > 0) {


    device = guestfs_lvm_canonical_lv_name (g, spec);
  }
  else if (match3 (g, spec, re_xdev, &type, &disk, &part)) {
    r = resolve_fstab_device_xdev (g, type, disk, part, &device);
    free (type);
    free (disk);
    free (part);
    if (r == -1)
      return NULL;
  }
  else if (match2 (g, spec, re_cciss, &disk, &part)) {
    r = resolve_fstab_device_cciss (g, disk, part, &device);
    free (disk);
    free (part);
    if (r == -1)
      return NULL;
  }
  else if (md_map && (disk = match1 (g, spec, re_mdN)) != NULL) {
    mdadm_app entry;
    entry.mdadm = disk;

    mdadm_app *app = hash_lookup (md_map, &entry);
    if (app) device = safe_strdup (g, app->app);

    free (disk);
  }
  else if (match3 (g, spec, re_freebsd, &disk, &slice, &part)) {


    int disk_i = guestfs___parse_unsigned_int (g, disk);
    int slice_i = guestfs___parse_unsigned_int (g, slice);
    int part_i = part[0] - 'a' ;
    free (disk);
    free (slice);
    free (part);

    if (disk_i != -1 && disk_i <= 26 &&
        slice_i > 0 && slice_i <= 1  &&
        part_i >= 0 && part_i < 26) {
      device = safe_asprintf (g, "/dev/sd%c%d", disk_i + 'a', part_i + 5);
    }
  }
  else if ((part = match1 (g, spec, re_diskbyid)) != NULL) {
    r = resolve_fstab_device_diskbyid (g, part, &device);
    free (part);
    if (r == -1)
      return NULL;
  }


  if (device == NULL)
    device = safe_strdup (g, spec);

  return device;
}
