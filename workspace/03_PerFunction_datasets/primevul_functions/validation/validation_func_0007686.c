check_architecture (guestfs_h *g, struct inspect_fs *fs)
{
  const char *binaries[] =
    { "/bin/bash", "/bin/ls", "/bin/echo", "/bin/rm", "/bin/sh" };
  size_t i;
  char *arch;

  for (i = 0; i < sizeof binaries / sizeof binaries[0]; ++i) {
    if (guestfs_is_file (g, binaries[i]) > 0) {

      guestfs_push_error_handler (g, NULL, NULL);
      arch = guestfs_file_architecture (g, binaries[i]);
      guestfs_pop_error_handler (g);

      if (arch) {


        fs->arch = arch;
        break;
      }
    }
  }
}
