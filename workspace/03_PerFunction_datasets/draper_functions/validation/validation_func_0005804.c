secfile_hash_insert(struct section_file *secfile,
                                struct entry *pentry)
{
  char buf[256];
  struct entry *hentry;

  if (NULL == secfile->hash.entries) {


    return TRUE;
  }

  entry_path(pentry, buf, sizeof(buf));
  if (entry_hash_replace_full(secfile->hash.entries, buf, pentry,
                              NULL, &hentry)) {
    entry_use(hentry);
    if (!secfile->allow_duplicates) {
      SECFILE_LOG(secfile, entry_section(hentry),
                  "Tried to insert same value twice: %s", buf);
      return FALSE;
    }
  }

  return TRUE;
}
