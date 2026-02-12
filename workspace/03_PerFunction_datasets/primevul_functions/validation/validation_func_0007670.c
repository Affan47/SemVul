check_hostname_redhat (guestfs_h *g, struct inspect_fs *fs)
{
  char *hostname;


  guestfs_push_error_handler (g, NULL, NULL);
  hostname = guestfs_aug_get (g, "/files/etc/sysconfig/network/HOSTNAME");
  guestfs_pop_error_handler (g);


  fs->hostname = hostname;
  return 0;
}
