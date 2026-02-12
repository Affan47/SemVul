check_filesystem (guestfs_h *g, const char *mountable,
                  const struct guestfs_internal_mountable *m,
                  int whole_device)
{
  if (extend_fses (g) == -1)
    return -1;

  int partnum = -1;
  if (!whole_device && m->im_type == MOUNTABLE_DEVICE) {
    guestfs_push_error_handler (g, NULL, NULL);
    partnum = guestfs_part_to_partnum (g, m->im_device);
    guestfs_pop_error_handler (g);
  }

  struct inspect_fs *fs = &g->fses[g->nr_fses-1];

  fs->mountable = safe_strdup (g, mountable);


  int is_dir_etc = guestfs_is_dir (g, "/etc") > 0;
  int is_dir_bin = guestfs_is_dir (g, "/bin") > 0;
  int is_dir_share = guestfs_is_dir (g, "/share") > 0;


  if (guestfs_is_file (g, "/grub/menu.lst") > 0 ||
      guestfs_is_file (g, "/grub/grub.conf") > 0 ||
      guestfs_is_file (g, "/grub2/grub.cfg") > 0)
    ;

  else if (is_dir_etc &&
           is_dir_bin &&
           guestfs_is_file (g, "/etc/freebsd-update.conf") > 0 &&
           guestfs_is_file (g, "/etc/fstab") > 0) {


    if (m->im_type == MOUNTABLE_DEVICE &&
        match (g, m->im_device, re_first_partition))
      return 0;

    fs->is_root = 1;
    fs->format = OS_FORMAT_INSTALLED;
    if (guestfs___check_freebsd_root (g, fs) == -1)
      return -1;
  }
  else if (is_dir_etc &&
           is_dir_bin &&
           guestfs_is_file (g, "/etc/fstab") > 0 &&
           guestfs_is_file (g, "/etc/release") > 0) {


    if (m->im_type == MOUNTABLE_DEVICE &&
        match (g, m->im_device, re_first_partition))
      return 0;

    fs->is_root = 1;
    fs->format = OS_FORMAT_INSTALLED;
    if (guestfs___check_netbsd_root (g, fs) == -1)
      return -1;
  }

  else if (guestfs_is_file (g, "/hurd/console") > 0 &&
           guestfs_is_file (g, "/hurd/hello") > 0 &&
           guestfs_is_file (g, "/hurd/null") > 0) {
    fs->is_root = 1;
    fs->format = OS_FORMAT_INSTALLED;
    if (guestfs___check_hurd_root (g, fs) == -1)
      return -1;
  }

  else if (is_dir_etc &&
           (is_dir_bin ||
            (guestfs_is_symlink (g, "/bin") > 0 &&
             guestfs_is_dir (g, "/usr/bin") > 0)) &&
           guestfs_is_file (g, "/etc/fstab") > 0) {
    fs->is_root = 1;
    fs->format = OS_FORMAT_INSTALLED;
    if (guestfs___check_linux_root (g, fs) == -1)
      return -1;
  }

  else if (is_dir_etc &&
           is_dir_bin &&
           is_dir_share &&
           guestfs_exists (g, "/local") == 0 &&
           guestfs_is_file (g, "/etc/fstab") == 0)
    ;

  else if (is_dir_etc &&
           is_dir_bin &&
           is_dir_share &&
           guestfs_exists (g, "/local") > 0 &&
           guestfs_is_file (g, "/etc/fstab") == 0)
    ;

  else if (guestfs_is_dir (g, "/log") > 0 &&
           guestfs_is_dir (g, "/run") > 0 &&
           guestfs_is_dir (g, "/spool") > 0)
    ;

  else if (guestfs___has_windows_systemroot (g) >= 0) {
    fs->is_root = 1;
    fs->format = OS_FORMAT_INSTALLED;
    if (guestfs___check_windows_root (g, fs) == -1)
      return -1;
  }

  else if (guestfs___is_dir_nocase (g, "/System Volume Information") > 0 &&
           guestfs___is_dir_nocase (g, "/Program Files") > 0)
    ;

  else if (guestfs___is_dir_nocase (g, "/System Volume Information") > 0)
    ;

  else if (guestfs___is_dir_nocase (g, "/FDOS") > 0 &&
           guestfs___is_file_nocase (g, "/FDOS/FREEDOS.BSS") > 0) {
    fs->is_root = 1;
    fs->format = OS_FORMAT_INSTALLED;
    fs->type = OS_TYPE_DOS;
    fs->distro = OS_DISTRO_FREEDOS;


    fs->arch = safe_strdup (g, "i386");
  }


  else if ((whole_device || partnum == 1) &&
           (guestfs_is_file (g, "/isolinux/isolinux.cfg") > 0 ||
            guestfs_is_dir (g, "/EFI/BOOT") > 0 ||
            guestfs_is_file (g, "/images/install.img") > 0 ||
            guestfs_is_dir (g, "/.disk") > 0 ||
            guestfs_is_file (g, "/.discinfo") > 0 ||
            guestfs_is_file (g, "/i386/txtsetup.sif") > 0 ||
            guestfs_is_file (g, "/amd64/txtsetup.sif") > 0 ||
            guestfs_is_file (g, "/freedos/freedos.ico") > 0)) {
    fs->is_root = 1;
    fs->format = OS_FORMAT_INSTALLER;
    if (guestfs___check_installer_root (g, fs) == -1)
      return -1;
  }


  guestfs___check_package_format (g, fs);
  guestfs___check_package_management (g, fs);

  return 0;
}
