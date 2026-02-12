ftp_retrieve_glob (struct url *u, struct url *original_url,
                   ccon *con, int action)
{
  struct fileinfo *f, *start;
  uerr_t res;

  con->cmd |= LEAVE_PENDING;

  res = ftp_get_listing (u, original_url, con, &start);
  if (res != RETROK)
    return res;


  int (*matcher) (const char *, const char *, int)
    = opt.ignore_case ? fnmatch_nocase : fnmatch;


#ifdef __VMS


  int (*cmp) (const char *, const char *)
    = opt.ignore_case ? strcasecmp : (int (*)())strcmp;
#else
  int (*cmp) (const char *, const char *)
    = opt.ignore_case ? strcasecmp : strcmp;
#endif

  f = start;
  while (f)
    {


      if ((opt.accepts || opt.rejects) &&
          f->type != FT_DIRECTORY && !acceptable (f->name))
        {
          logprintf (LOG_VERBOSE, _("Rejecting %s.\n"),
                     quote (f->name));
          f = delelement (f, &start);
          continue;
        }


      if (has_insecure_name_p (f->name) || is_invalid_entry (f))
        {
          logprintf (LOG_VERBOSE, _("Rejecting %s (Invalid Entry).\n"),
                     quote (f->name));
          f = delelement (f, &start);
          continue;
        }

      if (!accept_url (f->name))
        {
          logprintf (LOG_VERBOSE, _("%s is excluded/not-included through regex.\n"), f->name);
          f = delelement (f, &start);
          continue;
        }


      if (*u->file)
        {
          if (action == GLOB_GLOBALL)
            {
              int matchres = matcher (u->file, f->name, 0);
              if (matchres == -1)
                {
                  logprintf (LOG_NOTQUIET, _("Error matching %s against %s: %s\n"),
                             u->file, quotearg_style (escape_quoting_style, f->name),
                             strerror (errno));
                  freefileinfo (start);
                  return RETRBADPATTERN;
                }
              if (matchres == FNM_NOMATCH)
                {
                  f = delelement (f, &start);
                  continue;
                }
            }
          else if (action == GLOB_GETONE)
            {
              if (0 != cmp(u->file, f->name))
                {
                  f = delelement (f, &start);
                  continue;
                }
            }
        }
      f = f->next;
    }


  if (start)
    {

      res = ftp_retrieve_list (u, original_url, start, con);
    }
  else
    {
      if (action == GLOB_GLOBALL)
        {


          logprintf (LOG_VERBOSE, _("No matches on pattern %s.\n"),
                     quote (u->file));
        }
      else if (action == GLOB_GETONE)
        {

          con->st |= ON_YOUR_OWN;
          res = ftp_loop_internal (u, original_url, NULL, con, NULL, false);
          return res;
        }


    }
  freefileinfo (start);
  if (opt.quota && total_downloaded_bytes > opt.quota)
    return QUOTEXC;
  else
    return res;
}
