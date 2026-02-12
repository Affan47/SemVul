guestfs___check_for_filesystem_on (guestfs_h *g, const char *mountable)
{
  CLEANUP_FREE char *vfs_type = NULL;
  int is_swap, r;
  struct inspect_fs *fs;
  CLEANUP_FREE_INTERNAL_MOUNTABLE struct guestfs_internal_mountable *m = NULL;
  int whole_device = 0;


  guestfs_push_error_handler (g, NULL, NULL);
  vfs_type = guestfs_vfs_type (g, mountable);
  guestfs_pop_error_handler (g);

  is_swap = vfs_type && STREQ (vfs_type, "swap");
  debug (g, "check_for_filesystem_on: %s (%s)",
         mountable, vfs_type ? vfs_type : "failed to get vfs type");

  if (is_swap) {
    if (extend_fses (g) == -1)
      return -1;
    fs = &g->fses[g->nr_fses-1];
    fs->mountable = safe_strdup (g, mountable);
    return 0;
  }

  m = guestfs_internal_parse_mountable (g, mountable);
  if (m == NULL)
    return -1;


  if (m->im_type == MOUNTABLE_DEVICE) {
    whole_device = guestfs_is_whole_device (g, m->im_device);
    if (whole_device == -1) {
      return -1;
    }
  }

  if (whole_device) {
    if (extend_fses (g) == -1)
      return -1;
    fs = &g->fses[g->nr_fses-1];

    r = guestfs___check_installer_iso (g, fs, m->im_device);
    if (r == -1) {
      g->nr_fses--;
      return -1;
    }
    if (r > 0)
      return 0;


    g->nr_fses--;
  }


  guestfs_push_error_handler (g, NULL, NULL);
  if (vfs_type && STREQ (vfs_type, "ufs")) {

    r = guestfs_mount_vfs (g, "ro,ufstype=ufs2", "ufs", mountable, "/");
    if (r == -1)

      r = guestfs_mount_vfs (g, "ro,ufstype=44bsd", "ufs", mountable, "/");
  } else {
    r = guestfs_mount_ro (g, mountable, "/");
  }
  guestfs_pop_error_handler (g);
  if (r == -1)
    return 0;


  r = check_filesystem (g, mountable, m, whole_device);


  if (guestfs_umount_all (g) == -1)
    return -1;

  return r;
}
