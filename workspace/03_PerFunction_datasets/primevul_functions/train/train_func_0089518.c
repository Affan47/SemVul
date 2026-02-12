void imap_pretty_mailbox(char *path)
{
  struct ImapMbox home, target;
  struct Url url;
  char *delim = NULL;
  int tlen;
  int hlen = 0;
  bool home_match = false;

  if (imap_parse_path(path, &target) < 0)
    return;

  tlen = mutt_str_strlen(target.mbox);

  if (mx_is_imap(Folder) && !imap_parse_path(Folder, &home))
  {
    hlen = mutt_str_strlen(home.mbox);
    if (tlen && mutt_account_match(&home.account, &target.account) &&
        (mutt_str_strncmp(home.mbox, target.mbox, hlen) == 0))
    {
      if (hlen == 0)
        home_match = true;
      else if (ImapDelimChars)
      {
        for (delim = ImapDelimChars; *delim != '\0'; delim++)
          if (target.mbox[hlen] == *delim)
            home_match = true;
      }
    }
    FREE(&home.mbox);
  }


  if (home_match)
  {
    *path++ = '=';

    if (hlen == 0)
      hlen = -1;
    memcpy(path, target.mbox + hlen + 1, tlen - hlen - 1);
    path[tlen - hlen - 1] = '\0';
  }
  else
  {
    mutt_account_tourl(&target.account, &url);
    url.path = target.mbox;


    url_tostring(&url, path, 1024, 0);
  }

  FREE(&target.mbox);
}
