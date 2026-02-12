check_hostname_unix (guestfs_h *g, struct inspect_fs *fs)
{
  switch (fs->type) {
  case OS_TYPE_LINUX:
  case OS_TYPE_HURD:


    if (guestfs_is_file (g, "/etc/HOSTNAME")) {
      fs->hostname = guestfs___first_line_of_file (g, "/etc/HOSTNAME");
      if (fs->hostname == NULL)
        return -1;
      if (STREQ (fs->hostname, "")) {
        free (fs->hostname);
        fs->hostname = NULL;
      }
    }

    if (!fs->hostname && guestfs_is_file (g, "/etc/hostname")) {
      fs->hostname = guestfs___first_line_of_file (g, "/etc/hostname");
      if (fs->hostname == NULL)
        return -1;
      if (STREQ (fs->hostname, "")) {
        free (fs->hostname);
        fs->hostname = NULL;
      }
    }

    if (!fs->hostname && guestfs_is_file (g, "/etc/sysconfig/network")) {
      const char *configfiles[] = { "/etc/sysconfig/network", NULL };
      if (inspect_with_augeas (g, fs, configfiles,
                               check_hostname_redhat) == -1)
        return -1;
    }
    break;

  case OS_TYPE_FREEBSD:
  case OS_TYPE_NETBSD:


    if (guestfs_is_file (g, "/etc/rc.conf")) {
      if (check_hostname_freebsd (g, fs) == -1)
        return -1;
    }
    break;

  case OS_TYPE_WINDOWS:
  case OS_TYPE_DOS:
  case OS_TYPE_OPENBSD:
  case OS_TYPE_UNKNOWN:
    ;
  }

  return 0;
}
