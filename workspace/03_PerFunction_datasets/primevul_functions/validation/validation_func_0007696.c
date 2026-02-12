guestfs___check_hurd_root (guestfs_h *g, struct inspect_fs *fs)
{
  fs->type = OS_TYPE_HURD;

  if (guestfs_exists (g, "/etc/debian_version") > 0) {
    fs->distro = OS_DISTRO_DEBIAN;

    if (parse_release_file (g, fs, "/etc/debian_version") == -1)
      return -1;

    if (guestfs___parse_major_minor (g, fs) == -1)
      return -1;
  }


  check_architecture (g, fs);


  if (check_hostname_unix (g, fs) == -1)
    return -1;

  return 0;
}
