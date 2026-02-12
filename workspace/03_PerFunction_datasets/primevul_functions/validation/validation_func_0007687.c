add_fstab_entry (guestfs_h *g, struct inspect_fs *fs,
                 const char *mountable, const char *mountpoint)
{


  size_t n = fs->nr_fstab + 1;
  struct inspect_fstab_entry *p;

  p = realloc (fs->fstab, n * sizeof (struct inspect_fstab_entry));
  if (p == NULL) {
    perrorf (g, "realloc");
    return -1;
  }

  fs->fstab = p;
  fs->nr_fstab = n;


  fs->fstab[n-1].mountable = safe_strdup (g, mountable);
  fs->fstab[n-1].mountpoint = safe_strdup (g, mountpoint);

  debug (g, "fstab: mountable=%s mountpoint=%s", mountable, mountpoint);

  return 0;
}
