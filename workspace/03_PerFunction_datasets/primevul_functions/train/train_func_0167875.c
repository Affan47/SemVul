getftp (struct url *u, wgint passed_expected_bytes, wgint *qtyread,
        wgint restval, ccon *con, int count, wgint *last_expected_bytes,
        FILE *warc_tmp)
{
  int csock, dtsock, local_sock, res;
  uerr_t err = RETROK;
  FILE *fp;
  char *respline, *tms;
  const char *user, *passwd, *tmrate;
  int cmd = con->cmd;
  bool pasv_mode_open = false;
  wgint expected_bytes = 0;
  bool got_expected_bytes = false;
  bool rest_failed = false;
  int flags;
  wgint rd_size, previous_rd_size = 0;
  char type_char;
  bool try_again;
  bool list_a_used = false;

  assert (con != NULL);
  assert (con->target != NULL);


  assert (!((cmd & DO_LIST) && (cmd & DO_RETR)));

  assert ((cmd & (DO_LIST | DO_CWD | DO_RETR | DO_LOGIN)) != 0);

  *qtyread = restval;

  user = u->user;
  passwd = u->passwd;
  search_netrc (u->host, (const char **)&user, (const char **)&passwd, 1);
  user = user ? user : (opt.ftp_user ? opt.ftp_user : opt.user);
  if (!user) user = "anonymous";
  passwd = passwd ? passwd : (opt.ftp_passwd ? opt.ftp_passwd : opt.passwd);
  if (!passwd) passwd = "-wget@";

  dtsock = -1;
  local_sock = -1;
  con->dltime = 0;

  if (!(cmd & DO_LOGIN))
    csock = con->csock;
  else
    {
      char    *host = con->proxy ? con->proxy->host : u->host;
      int      port = con->proxy ? con->proxy->port : u->port;


      csock = connect_to_host (host, port);
      if (csock == E_HOST)
          return HOSTERR;
      else if (csock < 0)
          return (retryable_socket_connect_error (errno)
                  ? CONERROR : CONIMPOSSIBLE);

      if (cmd & LEAVE_PENDING)
        con->csock = csock;
      else
        con->csock = -1;


      logprintf (LOG_VERBOSE, _("Logging in as %s ... "),
                 quotearg_style (escape_quoting_style, user));
      if (opt.server_response)
        logputs (LOG_ALWAYS, "\n");
      if (con->proxy)
        {

          char *logname = concat_strings (user, "@", u->host, (char *) 0);
          err = ftp_login (csock, logname, passwd);
          xfree (logname);
        }
      else
        err = ftp_login (csock, user, passwd);


      switch (err)
        {
        case FTPRERR:
          logputs (LOG_VERBOSE, "\n");
          logputs (LOG_NOTQUIET, _("\
Error in server response, closing control connection.\n"));
          fd_close (csock);
          con->csock = -1;
          return err;
        case FTPSRVERR:
          logputs (LOG_VERBOSE, "\n");
          logputs (LOG_NOTQUIET, _("Error in server greeting.\n"));
          fd_close (csock);
          con->csock = -1;
          return err;
        case WRITEFAILED:
          logputs (LOG_VERBOSE, "\n");
          logputs (LOG_NOTQUIET,
                   _("Write failed, closing control connection.\n"));
          fd_close (csock);
          con->csock = -1;
          return err;
        case FTPLOGREFUSED:
          logputs (LOG_VERBOSE, "\n");
          logputs (LOG_NOTQUIET, _("The server refuses login.\n"));
          fd_close (csock);
          con->csock = -1;
          return FTPLOGREFUSED;
        case FTPLOGINC:
          logputs (LOG_VERBOSE, "\n");
          logputs (LOG_NOTQUIET, _("Login incorrect.\n"));
          fd_close (csock);
          con->csock = -1;
          return FTPLOGINC;
        case FTPOK:
          if (!opt.server_response)
            logputs (LOG_VERBOSE, _("Logged in!\n"));
          break;
        default:
          abort ();
        }

      if (!opt.server_response)
        logprintf (LOG_VERBOSE, "==> SYST ... ");
      err = ftp_syst (csock, &con->rs, &con->rsu);

      switch (err)
        {
        case FTPRERR:
          logputs (LOG_VERBOSE, "\n");
          logputs (LOG_NOTQUIET, _("\
Error in server response, closing control connection.\n"));
          fd_close (csock);
          con->csock = -1;
          return err;
        case FTPSRVERR:
          logputs (LOG_VERBOSE, "\n");
          logputs (LOG_NOTQUIET,
                   _("Server error, can't determine system type.\n"));
          break;
        case FTPOK:

          break;
        default:
          abort ();
        }
      if (!opt.server_response && err != FTPSRVERR)
        logputs (LOG_VERBOSE, _("done.    "));


      switch (con->rs)
        {
        case ST_VMS:


          DEBUGP (("\nVMS: I know it and I will use \"LIST\" as standard list command\n"));
          con->st |= LIST_AFTER_LIST_A_CHECK_DONE;
          con->st |= AVOID_LIST_A;
          break;
        case ST_UNIX:
          if (con->rsu == UST_MULTINET)
            {
              DEBUGP (("\nUNIX MultiNet: I know it and I will use \"LIST\" "
                       "as standard list command\n"));
              con->st |= LIST_AFTER_LIST_A_CHECK_DONE;
              con->st |= AVOID_LIST_A;
            }
          else if (con->rsu == UST_TYPE_L8)
            {
              DEBUGP (("\nUNIX TYPE L8: I know it and I will use \"LIST -a\" "
                       "as standard list command\n"));
              con->st |= LIST_AFTER_LIST_A_CHECK_DONE;
              con->st |= AVOID_LIST;
            }
          break;
        default:
          break;
        }


      if (!opt.server_response)
        logprintf (LOG_VERBOSE, "==> PWD ... ");
      err = ftp_pwd (csock, &con->id);

      switch (err)
        {
        case FTPRERR:
          logputs (LOG_VERBOSE, "\n");
          logputs (LOG_NOTQUIET, _("\
Error in server response, closing control connection.\n"));
          fd_close (csock);
          con->csock = -1;
          return err;
        case FTPSRVERR :

          xfree_null (con->id);
          con->id = xstrdup ("/");
          break;
        case FTPOK:

          break;
        default:
          abort ();
        }

#if 0


      if (con->rs == ST_VMS)
        {
          char *path = strchr (con->id, '[');
          char *pathend = path ? strchr (path + 1, ']') : NULL;
          if (!path || !pathend)
            DEBUGP (("Initial VMS directory not in the form [...]!\n"));
          else
            {
              char *idir = con->id;
              DEBUGP (("Preprocessing the initial VMS directory\n"));
              DEBUGP (("  old = '%s'\n", con->id));


              *idir++ = '/';
              for (++path; path < pathend; path++, idir++)
                *idir = *path == '.' ? '/' : *path;
              *idir = '\0';
              DEBUGP (("  new = '%s'\n\n", con->id));
            }
        }
#endif

      if (!opt.server_response)
        logputs (LOG_VERBOSE, _("done.\n"));


      type_char = ftp_process_type (u->params);
      if (!opt.server_response)
        logprintf (LOG_VERBOSE, "==> TYPE %c ... ", type_char);
      err = ftp_type (csock, type_char);

      switch (err)
        {
        case FTPRERR:
          logputs (LOG_VERBOSE, "\n");
          logputs (LOG_NOTQUIET, _("\
Error in server response, closing control connection.\n"));
          fd_close (csock);
          con->csock = -1;
          return err;
        case WRITEFAILED:
          logputs (LOG_VERBOSE, "\n");
          logputs (LOG_NOTQUIET,
                   _("Write failed, closing control connection.\n"));
          fd_close (csock);
          con->csock = -1;
          return err;
        case FTPUNKNOWNTYPE:
          logputs (LOG_VERBOSE, "\n");
          logprintf (LOG_NOTQUIET,
                     _("Unknown type `%c', closing control connection.\n"),
                     type_char);
          fd_close (csock);
          con->csock = -1;
          return err;
        case FTPOK:

          break;
        default:
          abort ();
        }
      if (!opt.server_response)
        logputs (LOG_VERBOSE, _("done.  "));
    }

  if (cmd & DO_CWD)
    {
      if (!*u->dir)
        logputs (LOG_VERBOSE, _("==> CWD not needed.\n"));
      else
        {
          const char *targ = NULL;
          int cwd_count;
          int cwd_end;
          int cwd_start;

          char *target = u->dir;

          DEBUGP (("changing working directory\n"));


          if (target[0] != '/'
              && !(con->rs != ST_UNIX
                   && c_isalpha (target[0])
                   && target[1] == ':')
              && (con->rs != ST_OS400)
              && (con->rs != ST_VMS))
            {
              int idlen = strlen (con->id);
              char *ntarget, *p;


              while (idlen > 0 && con->id[idlen - 1] == '/')
                --idlen;
              p = ntarget = (char *)alloca (idlen + 1 + strlen (u->dir) + 1);
              memcpy (p, con->id, idlen);
              p += idlen;
              *p++ = '/';
              strcpy (p, target);

              DEBUGP (("Prepended initial PWD to relative path:\n"));
              DEBUGP (("   pwd: '%s'\n   old: '%s'\n  new: '%s'\n",
                       con->id, target, ntarget));
              target = ntarget;
            }

#if 0


          if (con->rs == ST_VMS)
            {
              char *tmpp;
              char *ntarget = (char *)alloca (strlen (target) + 2);


              strcpy (ntarget, target);
              assert (*ntarget == '/');
              *ntarget = '[';
              for (tmpp = ntarget + 1; *tmpp; tmpp++)
                if (*tmpp == '/')
                  *tmpp = '.';
              *tmpp++ = ']';
              *tmpp = '\0';
              DEBUGP (("Changed file name to VMS syntax:\n"));
              DEBUGP (("  Unix: '%s'\n  VMS: '%s'\n", target, ntarget));
              target = ntarget;
            }
#endif


          if ((con->rs == ST_VMS) && (target[0] != '/'))
            {
              cwd_start = 0;
              DEBUGP (("Using two-step CWD for relative path.\n"));
            }
          else
            {

              cwd_start = 1;
            }


          if ((con->rs == ST_VMS) && (strchr( target, '/') != NULL))
            {
              cwd_end = 3;
              DEBUGP (("Using extra \"CWD []\" step for VMS server.\n"));
            }
          else
            {
              cwd_end = 2;
            }


          for (cwd_count = cwd_start; cwd_count < cwd_end; cwd_count++)
            {
          switch (cwd_count)
            {
              case 0:


                targ = con->id;
                break;

              case 1:


                targ = target;
                break;

              case 2:


                targ = "[]";
                break;

              default:

                assert (1);
            }

          if (!opt.server_response)
            logprintf (LOG_VERBOSE, "==> CWD (%d) %s ... ", cwd_count,
                       quotearg_style (escape_quoting_style, target));
          err = ftp_cwd (csock, targ);

          switch (err)
            {
            case FTPRERR:
              logputs (LOG_VERBOSE, "\n");
              logputs (LOG_NOTQUIET, _("\
Error in server response, closing control connection.\n"));
              fd_close (csock);
              con->csock = -1;
              return err;
            case WRITEFAILED:
              logputs (LOG_VERBOSE, "\n");
              logputs (LOG_NOTQUIET,
                       _("Write failed, closing control connection.\n"));
              fd_close (csock);
              con->csock = -1;
              return err;
            case FTPNSFOD:
              logputs (LOG_VERBOSE, "\n");
              logprintf (LOG_NOTQUIET, _("No such directory %s.\n\n"),
                         quote (u->dir));
              fd_close (csock);
              con->csock = -1;
              return err;
            case FTPOK:
              break;
            default:
              abort ();
            }
          if (!opt.server_response)
            logputs (LOG_VERBOSE, _("done.\n"));

        }


        }
    }
  else
    logputs (LOG_VERBOSE, _("==> CWD not required.\n"));

  if ((cmd & DO_RETR) && passed_expected_bytes == 0)
    {
      if (opt.verbose)
        {
          if (!opt.server_response)
            logprintf (LOG_VERBOSE, "==> SIZE %s ... ",
                       quotearg_style (escape_quoting_style, u->file));
        }

      err = ftp_size (csock, u->file, &expected_bytes);

      switch (err)
        {
        case FTPRERR:
        case FTPSRVERR:
          logputs (LOG_VERBOSE, "\n");
          logputs (LOG_NOTQUIET, _("\
Error in server response, closing control connection.\n"));
          fd_close (csock);
          con->csock = -1;
          return err;
        case FTPOK:
          got_expected_bytes = true;

          break;
        default:
          abort ();
        }
        if (!opt.server_response)
          {
            logprintf (LOG_VERBOSE, "%s\n",
                    expected_bytes ?
                    number_to_static_string (expected_bytes) :
                    _("done.\n"));
          }
    }

  if (cmd & DO_RETR && restval > 0 && restval == expected_bytes)
    {


      logputs (LOG_VERBOSE, _("File has already been retrieved.\n"));
      fd_close (csock);
      con->csock = -1;
      return RETRFINISHED;
    }

  do
  {
  try_again = false;

  if (cmd & (DO_LIST | DO_RETR))
    {
      if (opt.ftp_pasv)
        {
          ip_address passive_addr;
          int        passive_port;
          err = ftp_do_pasv (csock, &passive_addr, &passive_port);

          switch (err)
            {
            case FTPRERR:
              logputs (LOG_VERBOSE, "\n");
              logputs (LOG_NOTQUIET, _("\
Error in server response, closing control connection.\n"));
              fd_close (csock);
              con->csock = -1;
              return err;
            case WRITEFAILED:
              logputs (LOG_VERBOSE, "\n");
              logputs (LOG_NOTQUIET,
                       _("Write failed, closing control connection.\n"));
              fd_close (csock);
              con->csock = -1;
              return err;
            case FTPNOPASV:
              logputs (LOG_VERBOSE, "\n");
              logputs (LOG_NOTQUIET, _("Cannot initiate PASV transfer.\n"));
              break;
            case FTPINVPASV:
              logputs (LOG_VERBOSE, "\n");
              logputs (LOG_NOTQUIET, _("Cannot parse PASV response.\n"));
              break;
            case FTPOK:
              break;
            default:
              abort ();
            }
          if (err==FTPOK)
            {
              DEBUGP (("trying to connect to %s port %d\n",
                      print_address (&passive_addr), passive_port));
              dtsock = connect_to_ip (&passive_addr, passive_port, NULL);
              if (dtsock < 0)
                {
                  int save_errno = errno;
                  fd_close (csock);
                  con->csock = -1;
                  logprintf (LOG_VERBOSE, _("couldn't connect to %s port %d: %s\n"),
                             print_address (&passive_addr), passive_port,
                             strerror (save_errno));
                  return (retryable_socket_connect_error (save_errno)
                          ? CONERROR : CONIMPOSSIBLE);
                }

              pasv_mode_open = true;
              if (!opt.server_response)
                logputs (LOG_VERBOSE, _("done.    "));
            }
        }

      if (!pasv_mode_open)
        {
          err = ftp_do_port (csock, &local_sock);


          switch (err)
            {
            case FTPRERR:
              logputs (LOG_VERBOSE, "\n");
              logputs (LOG_NOTQUIET, _("\
Error in server response, closing control connection.\n"));
              fd_close (csock);
              con->csock = -1;
              fd_close (dtsock);
              fd_close (local_sock);
              return err;
            case WRITEFAILED:
              logputs (LOG_VERBOSE, "\n");
              logputs (LOG_NOTQUIET,
                       _("Write failed, closing control connection.\n"));
              fd_close (csock);
              con->csock = -1;
              fd_close (dtsock);
              fd_close (local_sock);
              return err;
            case CONSOCKERR:
              logputs (LOG_VERBOSE, "\n");
              logprintf (LOG_NOTQUIET, "socket: %s\n", strerror (errno));
              fd_close (csock);
              con->csock = -1;
              fd_close (dtsock);
              fd_close (local_sock);
              return err;
            case FTPSYSERR:
              logputs (LOG_VERBOSE, "\n");
              logprintf (LOG_NOTQUIET, _("Bind error (%s).\n"),
                         strerror (errno));
              fd_close (dtsock);
              return err;
            case FTPPORTERR:
              logputs (LOG_VERBOSE, "\n");
              logputs (LOG_NOTQUIET, _("Invalid PORT.\n"));
              fd_close (csock);
              con->csock = -1;
              fd_close (dtsock);
              fd_close (local_sock);
              return err;
            case FTPOK:
              break;
            default:
              abort ();
            }
          if (!opt.server_response)
            logputs (LOG_VERBOSE, _("done.    "));
        }
    }


  if (restval && (cmd & DO_RETR))
    {
      if (!opt.server_response)
        logprintf (LOG_VERBOSE, "==> REST %s ... ",
                   number_to_static_string (restval));
      err = ftp_rest (csock, restval);


      switch (err)
        {
        case FTPRERR:
          logputs (LOG_VERBOSE, "\n");
          logputs (LOG_NOTQUIET, _("\
Error in server response, closing control connection.\n"));
          fd_close (csock);
          con->csock = -1;
          fd_close (dtsock);
          fd_close (local_sock);
          return err;
        case WRITEFAILED:
          logputs (LOG_VERBOSE, "\n");
          logputs (LOG_NOTQUIET,
                   _("Write failed, closing control connection.\n"));
          fd_close (csock);
          con->csock = -1;
          fd_close (dtsock);
          fd_close (local_sock);
          return err;
        case FTPRESTFAIL:
          logputs (LOG_VERBOSE, _("\nREST failed, starting from scratch.\n"));
          rest_failed = true;
          break;
        case FTPOK:
          break;
        default:
          abort ();
        }
      if (err != FTPRESTFAIL && !opt.server_response)
        logputs (LOG_VERBOSE, _("done.    "));
    }

  if (cmd & DO_RETR)
    {


      if (opt.spider)
        {
          bool exists = false;
          struct fileinfo *f;
          uerr_t _res = ftp_get_listing (u, con, &f);


          con->cmd |= DO_RETR;
          if (_res == RETROK)
            {
              while (f)
                {
                  if (!strcmp (f->name, u->file))
                    {
                      exists = true;
                      break;
                    }
                  f = f->next;
                }
              if (exists)
                {
                  logputs (LOG_VERBOSE, "\n");
                  logprintf (LOG_NOTQUIET, _("File %s exists.\n"),
                             quote (u->file));
                }
              else
                {
                  logputs (LOG_VERBOSE, "\n");
                  logprintf (LOG_NOTQUIET, _("No such file %s.\n"),
                             quote (u->file));
                }
            }
          fd_close (csock);
          con->csock = -1;
          fd_close (dtsock);
          fd_close (local_sock);
          return RETRFINISHED;
        }

      if (opt.verbose)
        {
          if (!opt.server_response)
            {
              if (restval)
                logputs (LOG_VERBOSE, "\n");
              logprintf (LOG_VERBOSE, "==> RETR %s ... ",
                         quotearg_style (escape_quoting_style, u->file));
            }
        }

      err = ftp_retr (csock, u->file);

      switch (err)
        {
        case FTPRERR:
          logputs (LOG_VERBOSE, "\n");
          logputs (LOG_NOTQUIET, _("\
Error in server response, closing control connection.\n"));
          fd_close (csock);
          con->csock = -1;
          fd_close (dtsock);
          fd_close (local_sock);
          return err;
        case WRITEFAILED:
          logputs (LOG_VERBOSE, "\n");
          logputs (LOG_NOTQUIET,
                   _("Write failed, closing control connection.\n"));
          fd_close (csock);
          con->csock = -1;
          fd_close (dtsock);
          fd_close (local_sock);
          return err;
        case FTPNSFOD:
          logputs (LOG_VERBOSE, "\n");
          logprintf (LOG_NOTQUIET, _("No such file %s.\n\n"),
                     quote (u->file));
          fd_close (dtsock);
          fd_close (local_sock);
          return err;
        case FTPOK:
          break;
        default:
          abort ();
        }

      if (!opt.server_response)
        logputs (LOG_VERBOSE, _("done.\n"));

      if (! got_expected_bytes)
        expected_bytes = *last_expected_bytes;
    }

  if (cmd & DO_LIST)
    {
      if (!opt.server_response)
        logputs (LOG_VERBOSE, "==> LIST ... ");


      err = ftp_list (csock, NULL, con->st&AVOID_LIST_A, con->st&AVOID_LIST, &list_a_used);


      switch (err)
        {
        case FTPRERR:
          logputs (LOG_VERBOSE, "\n");
          logputs (LOG_NOTQUIET, _("\
Error in server response, closing control connection.\n"));
          fd_close (csock);
          con->csock = -1;
          fd_close (dtsock);
          fd_close (local_sock);
          return err;
        case WRITEFAILED:
          logputs (LOG_VERBOSE, "\n");
          logputs (LOG_NOTQUIET,
                   _("Write failed, closing control connection.\n"));
          fd_close (csock);
          con->csock = -1;
          fd_close (dtsock);
          fd_close (local_sock);
          return err;
        case FTPNSFOD:
          logputs (LOG_VERBOSE, "\n");
          logprintf (LOG_NOTQUIET, _("No such file or directory %s.\n\n"),
                     quote ("."));
          fd_close (dtsock);
          fd_close (local_sock);
          return err;
        case FTPOK:
          break;
        default:
          abort ();
        }
      if (!opt.server_response)
        logputs (LOG_VERBOSE, _("done.\n"));

      if (! got_expected_bytes)
        expected_bytes = *last_expected_bytes;
    }

  if (!(cmd & (DO_LIST | DO_RETR)) || (opt.spider && !(cmd & DO_LIST)))
    return RETRFINISHED;


  if (passed_expected_bytes && restval && expected_bytes
      && (expected_bytes == passed_expected_bytes - restval))
    {
      DEBUGP (("Lying FTP server found, adjusting.\n"));
      expected_bytes = passed_expected_bytes;
    }


  if (!pasv_mode_open)

    {


      dtsock = accept_connection (local_sock);
      if (dtsock < 0)
        {
          logprintf (LOG_NOTQUIET, "accept: %s\n", strerror (errno));
          return CONERROR;
        }
    }


  if (!output_stream || con->cmd & DO_LIST)
    {

#ifdef __VMS
      char *targ;

      targ = ods_conform (con->target);
      if (targ != con->target)
        {
          xfree (con->target);
          con->target = targ;
        }
#endif

      mkalldirs (con->target);
      if (opt.backups)
        rotate_backups (con->target);


#ifdef __VMS
# define BIN_TYPE_TRANSFER (type_char != 'A')
# define BIN_TYPE_FILE \
   ((!(cmd & DO_LIST)) && BIN_TYPE_TRANSFER && (opt.ftp_stmlf == 0))
# define FOPEN_OPT_ARGS "fop=sqo", "acc", acc_cb, &open_id
# define FOPEN_OPT_ARGS_BIN "ctx=bin,stm", "rfm=fix", "mrs=512" FOPEN_OPT_ARGS
#else
# define BIN_TYPE_FILE true
#endif

      if (restval && !(con->cmd & DO_LIST))
        {
#ifdef __VMS
          int open_id;

          if (BIN_TYPE_FILE)
            {
              open_id = 3;
              fp = fopen (con->target, "ab", FOPEN_OPT_ARGS_BIN);
            }
          else
            {
              open_id = 4;
              fp = fopen (con->target, "a", FOPEN_OPT_ARGS);
            }
#else
          fp = fopen (con->target, "ab");
#endif
        }
      else if (opt.noclobber || opt.always_rest || opt.timestamping || opt.dirstruct
               || opt.output_document || count > 0)
        {
          if (opt.unlink && file_exists_p (con->target))
            {
              if (unlink (con->target) < 0)
                {
                  logprintf (LOG_NOTQUIET, "%s: %s\n", con->target,
                    strerror (errno));
                    fd_close (csock);
                    con->csock = -1;
                    fd_close (dtsock);
                    fd_close (local_sock);
                    return UNLINKERR;
                }
            }

#ifdef __VMS
          int open_id;

          if (BIN_TYPE_FILE)
            {
              open_id = 5;
              fp = fopen (con->target, "wb", FOPEN_OPT_ARGS_BIN);
            }
          else
            {
              open_id = 6;
              fp = fopen (con->target, "w", FOPEN_OPT_ARGS);
            }
#else
          fp = fopen (con->target, "wb");
#endif
        }
      else
        {
          fp = fopen_excl (con->target, BIN_TYPE_FILE);
          if (!fp && errno == EEXIST)
            {


              logprintf (LOG_NOTQUIET, _("%s has sprung into existence.\n"),
                         con->target);
              fd_close (csock);
              con->csock = -1;
              fd_close (dtsock);
              fd_close (local_sock);
              return FOPEN_EXCL_ERR;
            }
        }
      if (!fp)
        {
          logprintf (LOG_NOTQUIET, "%s: %s\n", con->target, strerror (errno));
          fd_close (csock);
          con->csock = -1;
          fd_close (dtsock);
          fd_close (local_sock);
          return FOPENERR;
        }
    }
  else
    fp = output_stream;

  if (passed_expected_bytes)
    {
      print_length (passed_expected_bytes, restval, true);
      expected_bytes = passed_expected_bytes;

    }
  else if (expected_bytes)
    print_length (expected_bytes, restval, false);


  flags = 0;
  if (restval && rest_failed)
    flags |= rb_skip_startpos;
  rd_size = 0;
  res = fd_read_body (con->target, dtsock, fp,
                      expected_bytes ? expected_bytes - restval : 0,
                      restval, &rd_size, qtyread, &con->dltime, flags, warc_tmp);

  tms = datetime_str (time (NULL));
  tmrate = retr_rate (rd_size, con->dltime);
  total_download_time += con->dltime;

  fd_close (local_sock);

  if (!output_stream || con->cmd & DO_LIST)
    fclose (fp);


  if (res == -2 || (warc_tmp != NULL && res == -3))
    {
      logprintf (LOG_NOTQUIET, _("%s: %s, closing control connection.\n"),
                 con->target, strerror (errno));
      fd_close (csock);
      con->csock = -1;
      fd_close (dtsock);
      if (res == -2)
        return FWRITEERR;
      else if (res == -3)
        return WARC_TMP_FWRITEERR;
    }
  else if (res == -1)
    {
      logprintf (LOG_NOTQUIET, _("%s (%s) - Data connection: %s; "),
                 tms, tmrate, fd_errstr (dtsock));
      if (opt.server_response)
        logputs (LOG_ALWAYS, "\n");
    }
  fd_close (dtsock);


  err = ftp_response (csock, &respline);
  *last_expected_bytes = ftp_expected_bytes (respline);
  if (err != FTPOK)
    {


      if (res != -1)
        logprintf (LOG_NOTQUIET, "%s (%s) - ", tms, tmrate);
      logputs (LOG_NOTQUIET, _("Control connection closed.\n"));


      fd_close (csock);
      con->csock = -1;
      return FTPRETRINT;
    }


  if (*respline != '2')
    {
      xfree (respline);
      if (res != -1)
        logprintf (LOG_NOTQUIET, "%s (%s) - ", tms, tmrate);
      logputs (LOG_NOTQUIET, _("Data transfer aborted.\n"));
      return FTPRETRINT;
    }
  xfree (respline);

  if (res == -1)
    {


      return FTPRETRINT;
    }

  if (!(cmd & LEAVE_PENDING))
    {


      fd_close (csock);
      con->csock = -1;
    }


  if (con->cmd & DO_LIST)
    {
      if (opt.server_response)
        {


#ifdef __VMS
      char *targ;

      targ = ods_conform( con->target);
      if (targ != con->target)
        {
          xfree( con->target);
          con->target = targ;
        }
#endif

      mkalldirs (con->target);
      fp = fopen (con->target, "r");
      if (!fp)
        logprintf (LOG_ALWAYS, "%s: %s\n", con->target, strerror (errno));
      else
        {
          char *line = NULL;
          size_t bufsize = 0;
          ssize_t len;


          while ((len = getline (&line, &bufsize, fp)) > 0)
            {
              while (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r'))
                line[--len] = '\0';
              logprintf (LOG_ALWAYS, "%s\n",
                         quotearg_style (escape_quoting_style, line));
            }
          xfree (line);
          fclose (fp);
        }
        }


      if (!(con->st & LIST_AFTER_LIST_A_CHECK_DONE))
        {


          if (con->st & AVOID_LIST_A)
            {


              if (rd_size > previous_rd_size)
                {


                  con->st |= LIST_AFTER_LIST_A_CHECK_DONE;
                  DEBUGP (("LIST returned more data than \"LIST -a\": "
                           "I will use \"LIST\" as standard list command\n"));
                }
              else if (previous_rd_size > rd_size)
                {


                  con->st |= LIST_AFTER_LIST_A_CHECK_DONE;
                  con->st |= AVOID_LIST;
                  con->st &= ~AVOID_LIST_A;

                  try_again = true;
                  DEBUGP (("LIST returned less data than \"LIST -a\": I will "
                           "use \"LIST -a\" as standard list command\n"));
                }
              else
                {

                  if (rd_size == 0)
                    {


                      con->st &= ~AVOID_LIST_A;
                    }
                  else
                    {


                      con->st |= LIST_AFTER_LIST_A_CHECK_DONE;
                      con->st |= AVOID_LIST;
                      con->st &= ~AVOID_LIST_A;
                      DEBUGP (("LIST returned the same amount of data of "
                               "\"LIST -a\": I will use \"LIST -a\" as standard "
                               "list command\n"));
                    }
                }
            }
          else
            {

              if (list_a_used)
                {


                  previous_rd_size = rd_size;
                  try_again = true;
                  con->st |= AVOID_LIST_A;
                }
              else
                {


                  con->st |= LIST_AFTER_LIST_A_CHECK_DONE;
                  con->st |= AVOID_LIST_A;
                  DEBUGP (("\"LIST -a\" failed: I will use \"LIST\" "
                           "as standard list command\n"));
                }
            }
        }
    }
  } while (try_again);
  return RETRFINISHED;
}
