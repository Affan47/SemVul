inascii2 (char *magic, char *name, Stat *asb)
{
  auto uint namelen;
  auto char header[H_STRLEN2 + 1];
  PStat pasb;

  if (strncmp (magic, M_ASCII2, M_STRLEN) != 0)
    return (-1);
  if (inread (header, H_STRLEN2) < 0)
    return (warnarch ("Corrupt extended ASCII header", (off_t) H_STRLEN2));
  header[H_STRLEN2] = '\0';
  if (sscanf (header, PH_SCAN2, &pasb.PSt_dev,
             &pasb.PSt_ino, &pasb.PSt_mode, &pasb.PSt_uid,
             &pasb.PSt_gid, &pasb.PSt_nlink, &pasb.PSt_rdev,
             &pasb.PSt_mtime, &namelen, &pasb.PSt_size) != H_COUNT)
    return (warnarch ("Bad extended ASCII header", (off_t) H_STRLEN));

  asb->sb_dev = pasb.PSt_dev;
  asb->sb_ino = pasb.PSt_ino;
  asb->sb_mode = pasb.PSt_mode;
  asb->sb_uid = pasb.PSt_uid;
  asb->sb_gid = pasb.PSt_gid;
  asb->sb_nlink = pasb.PSt_nlink;
  asb->sb_rdev = pasb.PSt_rdev;
  asb->sb_mtime = pasb.PSt_mtime;
  asb->sb_size = pasb.PSt_size;

  if (namelen == 0 || namelen >= PATHSIZE)
    return (warnarch ("Bad ASCII pathname length", (off_t) H_STRLEN));
  if (inread (name, namelen) < 0)
    return (warnarch ("Corrupt ASCII pathname", (off_t) namelen));
  if (name[namelen - 1] != '\0')
    return (warnarch ("Bad ASCII pathname", (off_t) namelen));
  return (0);
}
