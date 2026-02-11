compare_from_file (struct locarhandle *ah, void *p1, uint32_t offset2,
		   uint32_t size)
{
  void *p2 = xmalloc (size);
  if (pread (ah->fd, p2, size, offset2) != size)
    WITH_CUR_LOCALE (error (4, errno,
			    _("cannot read data from locale archive")));

  int res = memcmp (p1, p2, size);
  free (p2);
  return res;
}
