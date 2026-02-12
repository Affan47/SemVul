log_write(unsigned int selector, int flags, const char *format, ...)
{
uschar * ptr;
int paniclogfd;
ssize_t written_len;
gstring gs = { .size = LOG_BUFFER_SIZE-1, .ptr = 0, .s = log_buffer };
gstring * g;
va_list ap;


if (panic_recurseflag)
  {
  uschar *extra = panic_save_buffer ? panic_save_buffer : US"";
  if (debug_file) debug_printf("%s%s", extra, log_buffer);
  if (log_stderr && log_stderr != debug_file)
    fprintf(log_stderr, "%s%s", extra, log_buffer);
  if (*extra) write_syslog(LOG_CRIT, extra);
  write_syslog(LOG_CRIT, log_buffer);
  die(US"exim: could not open panic log - aborting: see message(s) above",
    US"Unexpected log failure, please try later");
  }


if (!log_buffer)
  if (!(log_buffer = US malloc(LOG_BUFFER_SIZE)))
    {
    fprintf(stderr, "exim: failed to get store for log buffer\n");
    exim_exit(EXIT_FAILURE, NULL);
    }


if (!path_inspected)
  {
  BOOL multiple = FALSE;
  int old_pool = store_pool;

  store_pool = POOL_PERM;


  if (*log_file_path)
    {
    int sep = ':';
    uschar *s;
    const uschar *ss = log_file_path;

    logging_mode = 0;
    while ((s = string_nextinlist(&ss, &sep, log_buffer, LOG_BUFFER_SIZE)))
      {
      if (Ustrcmp(s, "syslog") == 0)
        logging_mode |= LOG_MODE_SYSLOG;
      else if (logging_mode & LOG_MODE_FILE)
	multiple = TRUE;
      else
        {
        logging_mode |= LOG_MODE_FILE;


        if (*s)
          file_path = string_copy(s);


        else
	  set_file_path();
        }
      }
    }


  if (logging_mode == 0)
    die(US"Neither syslog nor file logging set in log_file_path",
        US"Unexpected logging failure");


  if (logging_mode & LOG_MODE_FILE  &&  !file_path[0])
    file_path = string_sprintf("%s/log/%%slog", spool_directory);
  store_pool = old_pool;
  path_inspected = TRUE;


  if (multiple)
    log_write(0, LOG_MAIN|LOG_PANIC,
      "More than one path given in log_file_path: using %s", file_path);
  }


DEBUG(D_any|D_v)
  {
  int i;

  g = string_catn(&gs, US"LOG:", 4);


  for (i = 0; i < log_options_count; i++)
    {
    unsigned int bitnum = log_options[i].bit;
    if (bitnum < BITWORDSIZE && selector == BIT(bitnum))
      g = string_fmt_append(g, " %s", log_options[i].name);
    }

  g = string_fmt_append(g, "%s%s%s%s\n  ",
    flags & LOG_MAIN ?    " MAIN"   : "",
    flags & LOG_PANIC ?   " PANIC"  : "",
    (flags & LOG_PANIC_DIE) == LOG_PANIC_DIE ? " DIE" : "",
    flags & LOG_REJECT ?  " REJECT" : "");

  if (flags & LOG_CONFIG) g = log_config_info(g, flags);

  va_start(ap, format);
  i = g->ptr;
  if (!string_vformat(g, FALSE, format, ap))
    {
    g->ptr = i;
    g = string_cat(g, US"**** log string overflowed log buffer ****");
    }
  va_end(ap);

  g->size = LOG_BUFFER_SIZE;
  g = string_catn(g, US"\n", 1);
  debug_printf("%s", string_from_gstring(g));

  gs.size = LOG_BUFFER_SIZE-1;
  gs.ptr = 0;
  gs.s = log_buffer;
  }


if (!(flags & (LOG_MAIN|LOG_PANIC|LOG_REJECT)))
  log_write(0, LOG_MAIN|LOG_PANIC_DIE, "log_write called with no log "
    "flags set");


if (f.disable_logging)
  {
  DEBUG(D_any) debug_printf("log writing disabled\n");
  return;
  }


if (!write_rejectlog) flags &= ~LOG_REJECT;


g = string_fmt_append(&gs, "%s ", tod_stamp(tod_log));

if (LOGGING(pid))
  {
  if (!syslog_pid) pid_position[0] = g->ptr;
  g = string_fmt_append(g, "[%d] ", (int)getpid());
  if (!syslog_pid) pid_position[1] = g->ptr;
  }

if (f.really_exim && message_id[0] != 0)
  g = string_fmt_append(g, "%s ", message_id);

if (flags & LOG_CONFIG)
  g = log_config_info(g, flags);

va_start(ap, format);
  {
  int i = g->ptr;
  if (!string_vformat(g, FALSE, format, ap))
    {
    g->ptr = i;
    g = string_cat(g, US"**** log string overflowed log buffer ****\n");
    }
  }
va_end(ap);


if (   flags & LOG_SENDER
   && g->ptr < LOG_BUFFER_SIZE - 10 - Ustrlen(raw_sender))
  g = string_fmt_append(g, " from <%s>", raw_sender);


if (  flags & LOG_RECIPIENTS
   && g->ptr < LOG_BUFFER_SIZE - 6
   && raw_recipients_count > 0)
  {
  int i;
  g = string_fmt_append(g, " for");
  for (i = 0; i < raw_recipients_count; i++)
    {
    uschar * s = raw_recipients[i];
    if (LOG_BUFFER_SIZE - g->ptr < Ustrlen(s) + 3) break;
    g = string_fmt_append(g, " %s", s);
    }
  }

g = string_catn(g, US"\n", 1);
string_from_gstring(g);


if (!f.really_exim || f.log_testing_mode)
  {
  if (  !debug_selector
     && log_stderr
     && (selector == 0 || (selector & log_selector[0]) != 0)
    )
    if (host_checking)
      fprintf(log_stderr, "LOG: %s", CS(log_buffer + 20));
    else
      fprintf(log_stderr, "%s", CS log_buffer);

  if ((flags & LOG_PANIC_DIE) == LOG_PANIC_DIE) exim_exit(EXIT_FAILURE, US"");
  return;
  }


if (  flags & LOG_MAIN
   && (!selector ||  selector & log_selector[0]))
  {
  if (  logging_mode & LOG_MODE_SYSLOG
     && (syslog_duplication || !(flags & (LOG_REJECT|LOG_PANIC))))
    write_syslog(LOG_INFO, log_buffer);

  if (logging_mode & LOG_MODE_FILE)
    {
    struct stat statbuf;


    if (mainlog_datestamp)
      {
      uschar *nowstamp = tod_stamp(string_datestamp_type);
      if (Ustrncmp (mainlog_datestamp, nowstamp, Ustrlen(nowstamp)) != 0)
        {
        (void)close(mainlogfd);
        mainlogfd = -1;
        mainlog_inode = 0;
        mainlog_datestamp = NULL;
        }
      }


    if (mainlogfd >= 0)
      if (Ustat(mainlog_name, &statbuf) < 0 || statbuf.st_ino != mainlog_inode)
	mainlog_close();


    if (mainlogfd < 0)
      {
      open_log(&mainlogfd, lt_main, NULL);
      if (fstat(mainlogfd, &statbuf) >= 0) mainlog_inode = statbuf.st_ino;
      }


    written_len = write_to_fd_buf(mainlogfd, g->s, g->ptr);
    if (written_len != g->ptr)
      {
      log_write_failed(US"main log", g->ptr, written_len);

      }
    }
  }


if (flags & LOG_REJECT)
  {
  header_line *h;

  if (header_list && LOGGING(rejected_header))
    {
    uschar * p = g->s + g->ptr;
    int i;

    if (recipients_count > 0)
      {


      string_format(p, LOG_BUFFER_SIZE - g->ptr,
        "Envelope-from: <%s>\n", sender_address);
      while (*p) p++;
      g->ptr = p - g->s;


      string_format(p, LOG_BUFFER_SIZE - g->ptr,
        "Envelope-to: <%s>\n", recipients_list[0].address);
      while (*p) p++;
      g->ptr = p - g->s;

      for (i = 1; i < recipients_count && i < 5; i++)
        {
        string_format(p, LOG_BUFFER_SIZE - g->ptr, "    <%s>\n",
          recipients_list[i].address);
	while (*p) p++;
	g->ptr = p - g->s;
        }

      if (i < recipients_count)
        {
        string_format(p, LOG_BUFFER_SIZE - g->ptr,
          "    ...\n");
	while (*p) p++;
	g->ptr = p - g->s;
        }
      }


    for (h = header_list; h; h = h->next) if (h->text)
      {
      BOOL fitted = string_format(p, LOG_BUFFER_SIZE - g->ptr,
        "%c %s", h->type, h->text);
      while (*p) p++;
      g->ptr = p - g->s;
      if (!fitted)
        {
        g->ptr -= 100;
        if (g->s[g->ptr-1] == '\n') g->ptr--;
        g = string_cat(g, US"\n*** truncated ***\n");
        break;
        }
      }
    }


  if (  logging_mode & LOG_MODE_SYSLOG
     && (syslog_duplication || !(flags & LOG_PANIC)))
    write_syslog(LOG_NOTICE, string_from_gstring(g));


  if (logging_mode & LOG_MODE_FILE)
    {
    struct stat statbuf;

    if (rejectlog_datestamp)
      {
      uschar *nowstamp = tod_stamp(string_datestamp_type);
      if (Ustrncmp (rejectlog_datestamp, nowstamp, Ustrlen(nowstamp)) != 0)
        {
        (void)close(rejectlogfd);
        rejectlogfd = -1;
        rejectlog_inode = 0;
        rejectlog_datestamp = NULL;
        }
      }


    if (rejectlogfd >= 0)
      if (Ustat(rejectlog_name, &statbuf) < 0 ||
           statbuf.st_ino != rejectlog_inode)
        {
        (void)close(rejectlogfd);
        rejectlogfd = -1;
        rejectlog_inode = 0;
        }


    if (rejectlogfd < 0)
      {
      open_log(&rejectlogfd, lt_reject, NULL);
      if (fstat(rejectlogfd, &statbuf) >= 0) rejectlog_inode = statbuf.st_ino;
      }

    written_len = write_to_fd_buf(rejectlogfd, g->s, g->ptr);
    if (written_len != g->ptr)
      {
      log_write_failed(US"reject log", g->ptr, written_len);

      }
    }
  }


if (flags & LOG_PANIC)
  {
  if (log_stderr && log_stderr != debug_file && !mua_wrapper)
    fprintf(log_stderr, "%s", CS string_from_gstring(g));

  if (logging_mode & LOG_MODE_SYSLOG)
    write_syslog(LOG_ALERT, log_buffer);


  if (logging_mode & LOG_MODE_FILE)
    {
    panic_recurseflag = TRUE;
    open_log(&paniclogfd, lt_panic, NULL);
    panic_recurseflag = FALSE;

    if (panic_save_buffer)
      {
      int i = write(paniclogfd, panic_save_buffer, Ustrlen(panic_save_buffer));
      i = i;
      }

    written_len = write_to_fd_buf(paniclogfd, g->s, g->ptr);
    if (written_len != g->ptr)
      {
      int save_errno = errno;
      write_syslog(LOG_CRIT, log_buffer);
      sprintf(CS log_buffer, "write failed on panic log: length=%d result=%d "
        "errno=%d (%s)", g->ptr, (int)written_len, save_errno, strerror(save_errno));
      write_syslog(LOG_CRIT, string_from_gstring(g));
      flags |= LOG_PANIC_DIE;
      }

    (void)close(paniclogfd);
    }


  if ((flags & LOG_PANIC_DIE) != LOG_PANIC)
    die(NULL, US"Unexpected failure, please try later");
  }
}
