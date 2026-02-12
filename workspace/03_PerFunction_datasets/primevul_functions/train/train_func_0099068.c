void svr_mailowner(

  job   *pjob,
  int    mailpoint,
  int    force,
  char *text)

  {
  int         status = 0;
  int         numargs = 0;
  int         pipes[2];
  int         counter;
  pid_t       pid;
  char       *mailptr;
  char       *mailfrom = NULL;
  char        tmpBuf[LOG_BUF_SIZE];

  char       *sendmail_args[100];
  char        mailto[1024];
  FILE       *stream;

  struct array_strings *pas;

  if ((server.sv_attr[SRV_ATR_MailDomain].at_flags & ATR_VFLAG_SET) &&
      (server.sv_attr[SRV_ATR_MailDomain].at_val.at_str != NULL) &&
      (!strcasecmp("never", server.sv_attr[SRV_ATR_MailDomain].at_val.at_str)))
    {

    if (LOGLEVEL >= 3)
      {
      log_event(PBSEVENT_ERROR | PBSEVENT_ADMIN | PBSEVENT_JOB,
        PBS_EVENTCLASS_JOB,
        pjob->ji_qs.ji_jobid,
        "Not sending email: Mail domain set to 'never'\n");
      }

    return;
    }

  if (LOGLEVEL >= 3)
    {
    char tmpBuf[LOG_BUF_SIZE];

    snprintf(tmpBuf, LOG_BUF_SIZE, "preparing to send '%c' mail for job %s to %s (%.64s)\n",
             (char)mailpoint,
             pjob->ji_qs.ji_jobid,
             pjob->ji_wattr[JOB_ATR_job_owner].at_val.at_str,
             (text != NULL) ? text : "---");

    log_event(
      PBSEVENT_ERROR | PBSEVENT_ADMIN | PBSEVENT_JOB,
      PBS_EVENTCLASS_JOB,
      pjob->ji_qs.ji_jobid,
      tmpBuf);
    }


  if ((force != MAIL_FORCE) ||
    (server.sv_attr[(int)SRV_ATR_NoMailForce].at_val.at_long == TRUE))
    {

    if (pjob->ji_wattr[JOB_ATR_mailpnts].at_flags & ATR_VFLAG_SET)
      {
      if (*(pjob->ji_wattr[JOB_ATR_mailpnts].at_val.at_str) ==  MAIL_NONE)
        {

        log_event(PBSEVENT_JOB,
                  PBS_EVENTCLASS_JOB,
                  pjob->ji_qs.ji_jobid,
                  "Not sending email: job requested no e-mail");
        return;
        }

      if (strchr(
            pjob->ji_wattr[JOB_ATR_mailpnts].at_val.at_str,
            mailpoint) == NULL)
        {

        log_event(PBSEVENT_ERROR | PBSEVENT_ADMIN | PBSEVENT_JOB,
          PBS_EVENTCLASS_JOB,
          pjob->ji_qs.ji_jobid,
          "Not sending email: User does not want mail of this type.\n");

        return;
        }
      }
    else if (mailpoint != MAIL_ABORT)
      {
      log_event(PBSEVENT_ERROR | PBSEVENT_ADMIN | PBSEVENT_JOB,
        PBS_EVENTCLASS_JOB,
        pjob->ji_qs.ji_jobid,
        "Not sending email: Default mailpoint does not include this type.\n");

      return;
      }
    }


  if (fork())
    {
    return;
    }


  int numfds = sysconf(_SC_OPEN_MAX);
  while (--numfds > 0)
    close(numfds);


  if ((mailfrom = server.sv_attr[SRV_ATR_mailfrom].at_val.at_str) == NULL)
    {
    if (LOGLEVEL >= 5)
      {
      char tmpBuf[LOG_BUF_SIZE];

      snprintf(tmpBuf,sizeof(tmpBuf),
        "Updated mailto from user list: '%s'\n",
        mailto);
      log_event(PBSEVENT_ERROR | PBSEVENT_ADMIN | PBSEVENT_JOB,
        PBS_EVENTCLASS_JOB,
        pjob->ji_qs.ji_jobid,
        tmpBuf);
      }
    mailfrom = PBS_DEFAULT_MAIL;
    }


  *mailto = '\0';

  if (pjob->ji_wattr[JOB_ATR_mailuser].at_flags & ATR_VFLAG_SET)
    {

    pas = pjob->ji_wattr[JOB_ATR_mailuser].at_val.at_arst;

    if (pas != NULL)
      {
      int i;
      for (i = 0;i < pas->as_usedptr;i++)
        {
        if ((strlen(mailto) + strlen(pas->as_string[i]) + 2) < sizeof(mailto))
          {
          strcat(mailto, pas->as_string[i]);
          strcat(mailto, " ");
          }
        }
      }
    }
  else
    {

    if ((server.sv_attr[SRV_ATR_MailDomain].at_flags & ATR_VFLAG_SET) &&
        (server.sv_attr[SRV_ATR_MailDomain].at_val.at_str != NULL))
      {
      strcpy(mailto, pjob->ji_wattr[JOB_ATR_euser].at_val.at_str);
      strcat(mailto, "@");
      strcat(mailto, server.sv_attr[SRV_ATR_MailDomain].at_val.at_str);

      if (LOGLEVEL >= 5)
        {
        char tmpBuf[LOG_BUF_SIZE];

        snprintf(tmpBuf,sizeof(tmpBuf),
          "Updated mailto from job owner and mail domain: '%s'\n",
          mailto);
        log_event(PBSEVENT_ERROR | PBSEVENT_ADMIN | PBSEVENT_JOB,
          PBS_EVENTCLASS_JOB,
          pjob->ji_qs.ji_jobid,
          tmpBuf);
        }
      }
    else
      {
#ifdef TMAILDOMAIN
      strcpy(mailto, pjob->ji_wattr[JOB_ATR_euser].at_val.at_str);
      strcat(mailto, "@");
      strcat(mailto, TMAILDOMAIN);
#else
      strcpy(mailto, pjob->ji_wattr[JOB_ATR_job_owner].at_val.at_str);
#endif

      if (LOGLEVEL >= 5)
        {
        char tmpBuf[LOG_BUF_SIZE];

        snprintf(tmpBuf,sizeof(tmpBuf),
          "Updated mailto from job owner: '%s'\n",
          mailto);
        log_event(PBSEVENT_ERROR | PBSEVENT_ADMIN | PBSEVENT_JOB,
          PBS_EVENTCLASS_JOB,
          pjob->ji_qs.ji_jobid,
          tmpBuf);
        }
      }
    }

  sendmail_args[numargs++] = (char *)SENDMAIL_CMD;
  sendmail_args[numargs++] = (char *)"-f";
  sendmail_args[numargs++] = (char *)mailfrom;


  mailptr = strdup(mailto);
  sendmail_args[numargs++] = mailptr;
  for (counter=0; counter < (int)strlen(mailptr); counter++)
    {
    if (mailptr[counter] == ',')
      {
      mailptr[counter] = '\0';
      sendmail_args[numargs++] = mailptr + counter + 1;
      if (numargs >= 99)
        break;
      }
    }

  sendmail_args[numargs] = NULL;


  if (pipe(pipes) == -1)
    {
    snprintf(tmpBuf, sizeof(tmpBuf), "Unable to pipes for sending e-mail\n");
    log_event(PBSEVENT_ERROR | PBSEVENT_ADMIN | PBSEVENT_JOB,
      PBS_EVENTCLASS_JOB,
      pjob->ji_qs.ji_jobid,
      tmpBuf);

    free(mailptr);
    exit(-1);
    }

  if ((pid=fork()) == -1)
    {
    snprintf(tmpBuf, sizeof(tmpBuf), "Unable to fork for sending e-mail\n");
    log_event(PBSEVENT_ERROR | PBSEVENT_ADMIN | PBSEVENT_JOB,
      PBS_EVENTCLASS_JOB,
      pjob->ji_qs.ji_jobid,
      tmpBuf);

    free(mailptr);
    close(pipes[0]);
    close(pipes[1]);
    exit(-1);
    }
  else if (pid == 0)
    {


    dup2(pipes[0], 0);


    int numfds = sysconf(_SC_OPEN_MAX);
    while (--numfds > 0)
      close(numfds);

    execv(SENDMAIL_CMD, sendmail_args);

    exit(1);
    }
  else
    {


    close(pipes[0]);


    stream = fdopen(pipes[1], "w");
    write_email(stream, pjob, mailto, mailpoint, text);

    fflush(stream);


    if (fclose(stream) != 0)
      {
      snprintf(tmpBuf,sizeof(tmpBuf),
        "Piping mail body to sendmail closed: errno %d:%s\n",
        errno, strerror(errno));

      log_event(PBSEVENT_ERROR | PBSEVENT_ADMIN | PBSEVENT_JOB,
        PBS_EVENTCLASS_JOB,
        pjob->ji_qs.ji_jobid,
        tmpBuf);
      }


    if ((waitpid(pid, &status, WNOHANG) != 0) &&
        (status != 0))
      {
      snprintf(tmpBuf,sizeof(tmpBuf),
        "Sendmail command returned %d. Mail may not have been sent\n",
        status);

      log_event(PBSEVENT_ERROR | PBSEVENT_ADMIN | PBSEVENT_JOB,
        PBS_EVENTCLASS_JOB,
        pjob->ji_qs.ji_jobid,
        tmpBuf);
      }


    while (waitpid(-1, &status, WNOHANG) != 0)
      {

      }

    free(mailptr);
    exit(0);
    }


  exit(0);
  }
