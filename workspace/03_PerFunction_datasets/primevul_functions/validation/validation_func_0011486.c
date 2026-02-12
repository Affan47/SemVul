static int imap_tags_edit(struct Mailbox *m, const char *tags, char *buf, size_t buflen)
{
  struct ImapMboxData *mdata = imap_mdata_get(m);
  if (!mdata)
    return -1;

  char *new_tag = NULL;
  char *checker = NULL;


  if (!imap_has_flag(&mdata->flags, NULL))
  {
    mutt_error(_("IMAP server doesn't support custom flags"));
    return -1;
  }

  *buf = '\0';
  if (tags)
    mutt_str_copy(buf, tags, buflen);

  if (mutt_get_field("Tags: ", buf, buflen, MUTT_COMP_NO_FLAGS) != 0)
    return -1;


  new_tag = buf;
  checker = buf;
  SKIPWS(checker);
  while (*checker != '\0')
  {
    if ((*checker < 32) || (*checker >= 127) ||
        (*checker == 40) ||
        (*checker == 41) ||
        (*checker == 60) ||
        (*checker == 62) ||
        (*checker == 64) ||
        (*checker == 44) ||
        (*checker == 59) ||
        (*checker == 58) ||
        (*checker == 92) ||
        (*checker == 34) ||
        (*checker == 46) ||
        (*checker == 91) ||
        (*checker == 93))
    {
      mutt_error(_("Invalid IMAP flags"));
      return 0;
    }


    while ((checker[0] == ' ') && (checker[1] == ' '))
      checker++;


    *new_tag++ = *checker++;
  }
  *new_tag = '\0';
  new_tag = buf;
  mutt_str_remove_trailing_ws(new_tag);

  return !mutt_str_equal(tags, buf);
}
