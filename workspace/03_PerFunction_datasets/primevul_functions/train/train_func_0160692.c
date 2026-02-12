queue_run(uschar *start_id, uschar *stop_id, BOOL recurse)
{
BOOL force_delivery = f.queue_run_force || deliver_selectstring != NULL ||
  deliver_selectstring_sender != NULL;
const pcre *selectstring_regex = NULL;
const pcre *selectstring_regex_sender = NULL;
uschar *log_detail = NULL;
int subcount = 0;
int i;
uschar subdirs[64];


queue_domains = NULL;
queue_smtp_domains = NULL;
f.queue_smtp = f.queue_2stage;

queue_run_pid = getpid();
f.queue_running = TRUE;


if (!recurse)
  {
  uschar extras[8];
  uschar *p = extras;

  if (f.queue_2stage) *p++ = 'q';
  if (f.queue_run_first_delivery) *p++ = 'i';
  if (f.queue_run_force) *p++ = 'f';
  if (f.deliver_force_thaw) *p++ = 'f';
  if (f.queue_run_local) *p++ = 'l';
  *p = 0;

  p = big_buffer;
  p += sprintf(CS p, "pid=%d", (int)queue_run_pid);

  if (extras[0] != 0)
    p += sprintf(CS p, " -q%s", extras);

  if (deliver_selectstring)
    p += sprintf(CS p, " -R%s %s", f.deliver_selectstring_regex? "r" : "",
      deliver_selectstring);

  if (deliver_selectstring_sender)
    p += sprintf(CS p, " -S%s %s", f.deliver_selectstring_sender_regex? "r" : "",
      deliver_selectstring_sender);

  log_detail = string_copy(big_buffer);
  if (*queue_name)
    log_write(L_queue_run, LOG_MAIN, "Start '%s' queue run: %s",
      queue_name, log_detail);
  else
    log_write(L_queue_run, LOG_MAIN, "Start queue run: %s", log_detail);
  }


if (deliver_selectstring && f.deliver_selectstring_regex)
  selectstring_regex = regex_must_compile(deliver_selectstring, TRUE, FALSE);

if (deliver_selectstring_sender && f.deliver_selectstring_sender_regex)
  selectstring_regex_sender =
    regex_must_compile(deliver_selectstring_sender, TRUE, FALSE);


for (i = queue_run_in_order ? -1 : 0;
     i <= (queue_run_in_order ? -1 : subcount);
     i++)
  {
  queue_filename * fq;
  void *reset_point1 = store_get(0);

  DEBUG(D_queue_run)
    {
    if (i == 0)
      debug_printf("queue running main directory\n");
    else if (i == -1)
      debug_printf("queue running combined directories\n");
    else
      debug_printf("queue running subdirectory '%c'\n", subdirs[i]);
    }

  for (fq = queue_get_spool_list(i, subdirs, &subcount, !queue_run_in_order);
       fq;
       fq = fq->next)
    {
    pid_t pid;
    int status;
    int pfd[2];
    struct stat statbuf;
    uschar buffer[256];


    if (!f.queue_run_force && deliver_queue_load_max >= 0)
      if ((load_average = os_getloadavg()) > deliver_queue_load_max)
        {
        log_write(L_queue_run, LOG_MAIN, "Abandon queue run: %s (load %.2f, max %.2f)",
          log_detail,
          (double)load_average/1000.0,
          (double)deliver_queue_load_max/1000.0);
        i = subcount;
        break;
        }
      else
        DEBUG(D_load) debug_printf("load average = %.2f max = %.2f\n",
          (double)load_average/1000.0,
          (double)deliver_queue_load_max/1000.0);


    if (stop_id && Ustrncmp(fq->text, stop_id, MESSAGE_ID_LENGTH) > 0)
      continue;
    if (start_id && Ustrncmp(fq->text, start_id, MESSAGE_ID_LENGTH) < 0)
      continue;


    message_subdir[0] = fq->dir_uschar;
    if (Ustat(spool_fname(US"input", message_subdir, fq->text, US""), &statbuf) < 0)
      continue;


    if (deliver_selectstring || deliver_selectstring_sender ||
        f.queue_run_first_delivery)
      {
      BOOL wanted = TRUE;
      BOOL orig_dont_deliver = f.dont_deliver;
      void *reset_point2 = store_get(0);


      if (spool_read_header(fq->text, FALSE, TRUE) != spool_read_OK) continue;
      f.dont_deliver = orig_dont_deliver;


      if (f.deliver_freeze && !f.deliver_force_thaw)
        {
        log_write(L_skip_delivery, LOG_MAIN, "Message is frozen");
        wanted = FALSE;
        }


      else if (f.queue_run_first_delivery && !f.deliver_firsttime)
        {
        DEBUG(D_queue_run) debug_printf("%s: not first delivery\n", fq->text);
        wanted = FALSE;
        }


      else if (  deliver_selectstring_sender
	      && !(f.deliver_selectstring_sender_regex
		  ? (pcre_exec(selectstring_regex_sender, NULL,
		      CS sender_address, Ustrlen(sender_address), 0, PCRE_EOPT,
		      NULL, 0) >= 0)
		  : (strstric(sender_address, deliver_selectstring_sender, FALSE)
		      != NULL)
	      )   )
        {
        DEBUG(D_queue_run) debug_printf("%s: sender address did not match %s\n",
          fq->text, deliver_selectstring_sender);
        wanted = FALSE;
        }


      else if (deliver_selectstring)
        {
        int i;
        for (i = 0; i < recipients_count; i++)
          {
          uschar *address = recipients_list[i].address;
          if (  (f.deliver_selectstring_regex
		? (pcre_exec(selectstring_regex, NULL, CS address,
		     Ustrlen(address), 0, PCRE_EOPT, NULL, 0) >= 0)
                : (strstric(address, deliver_selectstring, FALSE) != NULL)
		)
             && tree_search(tree_nonrecipients, address) == NULL
	     )
            break;
          }

        if (i >= recipients_count)
          {
          DEBUG(D_queue_run)
            debug_printf("%s: no recipient address matched %s\n",
              fq->text, deliver_selectstring);
          wanted = FALSE;
          }
        }


      spool_clear_header_globals();
      store_reset(reset_point2);
      if (!wanted) continue;
      }


    if (pipe(pfd) < 0)
      log_write(0, LOG_MAIN|LOG_PANIC_DIE, "failed to create pipe in queue "
        "runner process %d: %s", queue_run_pid, strerror(errno));
    queue_run_pipe = pfd[pipe_write];


    if (queue_run_pipe == 0)
      {
      queue_run_pipe = dup(queue_run_pipe);
      (void)close(0);
      }


    search_tidyup();


    set_process_info("running queue: %s", fq->text);
    fq->text[SPOOL_NAME_LENGTH-2] = 0;
    if ((pid = fork()) == 0)
      {
      int rc;
      if (f.running_in_test_harness) millisleep(100);
      (void)close(pfd[pipe_read]);
      rc = deliver_message(fq->text, force_delivery, FALSE);
      _exit(rc == DELIVER_NOT_ATTEMPTED);
      }
    if (pid < 0)
      log_write(0, LOG_MAIN|LOG_PANIC_DIE, "fork of delivery process from "
        "queue runner %d failed\n", queue_run_pid);


    (void)close(pfd[pipe_write]);
    set_process_info("running queue: waiting for %s (%d)", fq->text, pid);
    while (wait(&status) != pid);


    if ((status & 0xffff) == 0) force_delivery = f.queue_run_force;


    else if ((status & 0x00ff) != 0)
      log_write(0, LOG_MAIN|LOG_PANIC,
        "queue run: process %d crashed with signal %d while delivering %s",
        (int)pid, status & 0x00ff, fq->text);


    set_process_info("running queue: waiting for children of %d", pid);
    if ((status = read(pfd[pipe_read], buffer, sizeof(buffer))) != 0)
      log_write(0, LOG_MAIN|LOG_PANIC, "queue run: %s on pipe",
		status > 0 ? "unexpected data" : "error");
    (void)close(pfd[pipe_read]);
    set_process_info("running queue");


    if (f.running_in_test_harness && !f.queue_2stage)
      {
      uschar *fqtnext = Ustrchr(fudged_queue_times, '/');
      if (fqtnext != NULL) fudged_queue_times = fqtnext + 1;
      }
    }

  tree_nonrecipients = NULL;
  store_reset(reset_point1);


  if (i == 0 && subcount > 1 && !queue_run_in_order)
    {
    int j, r;
    for (j = 1; j <= subcount; j++)
      if ((r = random_number(100)) >= 50)
        {
        int k = (r % subcount) + 1;
        int x = subdirs[j];
        subdirs[j] = subdirs[k];
        subdirs[k] = x;
        }
    }
  }


if (f.queue_2stage)
  {
  f.queue_2stage = FALSE;
  queue_run(start_id, stop_id, TRUE);
  }


if (!recurse)
  if (*queue_name)
    log_write(L_queue_run, LOG_MAIN, "End '%s' queue run: %s",
      queue_name, log_detail);
  else
    log_write(L_queue_run, LOG_MAIN, "End queue run: %s", log_detail);
}
