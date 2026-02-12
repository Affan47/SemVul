char *imap_fix_path(char delim, const char *mailbox, char *path, size_t plen)
{
  int i = 0;
  for (; mailbox && *mailbox && (i < plen - 1); i++)
  {
    const char *const c_imap_delim_chars =
        cs_subset_string(NeoMutt->sub, "imap_delim_chars");
    if (*mailbox == delim || (!delim && strchr(NONULL(c_imap_delim_chars), *mailbox)))
    {
      delim = *mailbox;

      while (*mailbox && *(mailbox + 1) == delim)
        mailbox++;
    }
    path[i] = *mailbox++;
  }


  if (i && path[i - 1] == delim)
    i--;


  path[i] = '\0';
  return path;
}
