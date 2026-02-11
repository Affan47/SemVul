check_gaiconf_mtime (const struct stat64 *st)
{
  return (st->st_mtim.tv_sec == gaiconf_mtime.tv_sec
          && st->st_mtim.tv_nsec == gaiconf_mtime.tv_nsec);
}
