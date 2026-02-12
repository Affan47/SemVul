par_read_pipe(int poffset, BOOL eop)
{
host_item *h;
pardata *p = parlist + poffset;
address_item *addrlist = p->addrlist;
address_item *addr = p->addr;
pid_t pid = p->pid;
int fd = p->fd;

uschar *msg = p->msg;
BOOL done = p->done;


DEBUG(D_deliver) debug_printf("reading pipe for subprocess %d (%s)\n",
  (int)p->pid, eop? "ended" : "not ended yet");

while (!done)
  {
  retry_item *r, **rp;
  uschar pipeheader[PIPE_HEADER_SIZE+1];
  uschar *id = &pipeheader[0];
  uschar *subid = &pipeheader[1];
  uschar *ptr = big_buffer;
  size_t required = PIPE_HEADER_SIZE;
  ssize_t got;

  DEBUG(D_deliver) debug_printf(
    "expect %lu bytes (pipeheader) from tpt process %d\n", (u_long)required, pid);


  if ((got = readn(fd, pipeheader, required)) != required)
    {
    msg = string_sprintf("got " SSIZE_T_FMT " of %d bytes (pipeheader) "
      "from transport process %d for transport %s",
      got, PIPE_HEADER_SIZE, pid, addr->transport->driver_name);
    done = TRUE;
    break;
    }

  pipeheader[PIPE_HEADER_SIZE] = '\0';
  DEBUG(D_deliver)
    debug_printf("got %ld bytes (pipeheader) from transport process %d\n",
      (long) got, pid);

  {


  char *endc;
  required = Ustrtol(pipeheader+2, &endc, 10);
  if (*endc)
    {
    msg = string_sprintf("failed to read pipe "
      "from transport process %d for transport %s: error decoding size from header",
      pid, addr->transport->driver_name);
    done = TRUE;
    break;
    }
  }

  DEBUG(D_deliver)
    debug_printf("expect %lu bytes (pipedata) from transport process %d\n",
      (u_long)required, pid);


  if ((got = readn(fd, big_buffer, required)) != required)
    {
    msg = string_sprintf("got only " SSIZE_T_FMT " of " SIZE_T_FMT
      " bytes (pipedata) from transport process %d for transport %s",
      got, required, pid, addr->transport->driver_name);
    done = TRUE;
    break;
    }


  switch (*id)
    {


    case 'H':
      for (h = addrlist->host_list; h; h = h->next)
	{
	if (!h->address || Ustrcmp(h->address, ptr+2) != 0) continue;
	h->status = ptr[0];
	h->why = ptr[1];
	}
      ptr += 2;
      while (*ptr++);
      break;


    case 'R':
      if (!addr) goto ADDR_MISMATCH;

      DEBUG(D_deliver|D_retry)
	debug_printf("reading retry information for %s from subprocess\n",
	  ptr+1);


      for (rp = &addr->retries; (r = *rp); rp = &r->next)
	if (Ustrcmp(r->key, ptr+1) == 0)
	  {
	  if (!(r->flags & rf_delete)) break;
	  *rp = r->next;
	  DEBUG(D_deliver|D_retry)
	    debug_printf("  existing delete item dropped\n");
	  }


      if (!r || !(*ptr & rf_delete))
	{
	r = store_get(sizeof(retry_item));
	r->next = addr->retries;
	addr->retries = r;
	r->flags = *ptr++;
	r->key = string_copy(ptr);
	while (*ptr++);
	memcpy(&r->basic_errno, ptr, sizeof(r->basic_errno));
	ptr += sizeof(r->basic_errno);
	memcpy(&r->more_errno, ptr, sizeof(r->more_errno));
	ptr += sizeof(r->more_errno);
	r->message = *ptr ? string_copy(ptr) : NULL;
	DEBUG(D_deliver|D_retry) debug_printf("  added %s item\n",
	    r->flags & rf_delete ? "delete" : "retry");
	}

      else
	{
	DEBUG(D_deliver|D_retry)
	  debug_printf("  delete item not added: non-delete item exists\n");
	ptr++;
	while(*ptr++);
	ptr += sizeof(r->basic_errno) + sizeof(r->more_errno);
	}

      while(*ptr++);
      break;


    case 'S':
      memcpy(&(p->transport_count), ptr, sizeof(transport_count));
      ptr += sizeof(transport_count);
      break;


#ifdef SUPPORT_TLS
    case 'X':
      if (!addr) goto ADDR_MISMATCH;
      switch (*subid)
	{
	case '1':
	  addr->cipher = NULL;
	  addr->peerdn = NULL;

	  if (*ptr)
	    addr->cipher = string_copy(ptr);
	  while (*ptr++);
	  if (*ptr)
	    addr->peerdn = string_copy(ptr);
	  break;

	case '2':
	  if (*ptr)
	    (void) tls_import_cert(ptr, &addr->peercert);
	  else
	    addr->peercert = NULL;
	  break;

	case '3':
	  if (*ptr)
	    (void) tls_import_cert(ptr, &addr->ourcert);
	  else
	    addr->ourcert = NULL;
	  break;

# ifndef DISABLE_OCSP
	case '4':
	  addr->ocsp = *ptr ? *ptr - '0' : OCSP_NOT_REQ;
	  break;
# endif
	}
      while (*ptr++);
      break;
#endif

    case 'C':
      switch (*subid)
	{
	case '1': addr->authenticator = *ptr ? string_copy(ptr) : NULL; break;
	case '2': addr->auth_id = *ptr ? string_copy(ptr) : NULL;	break;
	case '3': addr->auth_sndr = *ptr ? string_copy(ptr) : NULL;	break;
	}
      while (*ptr++);
      break;

#ifndef DISABLE_PRDR
    case 'P':
      setflag(addr, af_prdr_used);
      break;
#endif

    case 'L':
      switch (*subid)
	{
#ifdef EXPERIMENTAL_PIPE_CONNECT
	case 2: setflag(addr, af_early_pipe);
#endif
	case 1: setflag(addr, af_pipelining); break;
	}
      break;

    case 'K':
      setflag(addr, af_chunking_used);
      break;

    case 'T':
      setflag(addr, af_tcp_fastopen_conn);
      if (*subid > '0') setflag(addr, af_tcp_fastopen);
      if (*subid > '1') setflag(addr, af_tcp_fastopen_data);
      break;

    case 'D':
      if (!addr) goto ADDR_MISMATCH;
      memcpy(&(addr->dsn_aware), ptr, sizeof(addr->dsn_aware));
      ptr += sizeof(addr->dsn_aware);
      DEBUG(D_deliver) debug_printf("DSN read: addr->dsn_aware = %d\n", addr->dsn_aware);
      break;

    case 'A':
      if (!addr)
	{
	ADDR_MISMATCH:
	msg = string_sprintf("address count mismatch for data read from pipe "
	  "for transport process %d for transport %s", pid,
	    addrlist->transport->driver_name);
	done = TRUE;
	break;
	}

      switch (*subid)
	{
  #ifdef SUPPORT_SOCKS
	case '2':
	  proxy_session = TRUE;
	  if (*ptr == 0)
	    ptr++;
	  else
	    {
	    proxy_local_address = string_copy(ptr);
	    while(*ptr++);
	    memcpy(&proxy_local_port, ptr, sizeof(proxy_local_port));
	    ptr += sizeof(proxy_local_port);
	    }
	  break;
  #endif

  #ifdef EXPERIMENTAL_DSN_INFO
	case '1':

	  addr->smtp_greeting = string_copy(ptr);
	  while(*ptr++);
	  addr->helo_response = string_copy(ptr);
	  while(*ptr++);
	  break;
  #endif

	case '0':
	  DEBUG(D_deliver) debug_printf("A0 %s tret %d\n", addr->address, *ptr);
	  addr->transport_return = *ptr++;
	  addr->special_action = *ptr++;
	  memcpy(&addr->basic_errno, ptr, sizeof(addr->basic_errno));
	  ptr += sizeof(addr->basic_errno);
	  memcpy(&addr->more_errno, ptr, sizeof(addr->more_errno));
	  ptr += sizeof(addr->more_errno);
	  memcpy(&addr->delivery_usec, ptr, sizeof(addr->delivery_usec));
	  ptr += sizeof(addr->delivery_usec);
	  memcpy(&addr->flags, ptr, sizeof(addr->flags));
	  ptr += sizeof(addr->flags);
	  addr->message = *ptr ? string_copy(ptr) : NULL;
	  while(*ptr++);
	  addr->user_message = *ptr ? string_copy(ptr) : NULL;
	  while(*ptr++);


	  if (*ptr)
	    {
	    h = store_get(sizeof(host_item));
	    h->name = string_copy(ptr);
	    while (*ptr++);
	    h->address = string_copy(ptr);
	    while(*ptr++);
	    memcpy(&h->port, ptr, sizeof(h->port));
	    ptr += sizeof(h->port);
	    h->dnssec = *ptr == '2' ? DS_YES
		      : *ptr == '1' ? DS_NO
		      : DS_UNK;
	    ptr++;
	    addr->host_used = h;
	    }
	  else ptr++;


	  addr = addr->next;
	  break;
	}
      break;


    case 'I':
      if (*ptr) sending_ip_address = string_copy(ptr);
      while (*ptr++) ;
      if (*ptr) sending_port = atoi(CS ptr);
      while (*ptr++) ;
      break;


    case 'Z':
      if (*ptr == '0')
	{
	continue_transport = NULL;
	continue_hostname = NULL;
	}
      done = TRUE;
      DEBUG(D_deliver) debug_printf("Z0%c item read\n", *ptr);
      break;


    default:
      msg = string_sprintf("malformed data (%d) read from pipe for transport "
	"process %d for transport %s", ptr[-1], pid,
	  addr->transport->driver_name);
      done = TRUE;
      break;
    }
  }


p->done = done;


if (!eop && !done)
  {
  p->addr = addr;
  p->msg = msg;
  return FALSE;
  }


(void)close(fd);
p->fd = -1;


if (!msg && addr)
  msg = string_sprintf("insufficient address data read from pipe "
    "for transport process %d for transport %s", pid,
      addr->transport->driver_name);


if (msg)
  for (addr = addrlist; addr; addr = addr->next)
    {
    addr->transport_return = DEFER;
    addr->special_action = SPECIAL_FREEZE;
    addr->message = msg;
    log_write(0, LOG_MAIN|LOG_PANIC, "Delivery status for %s: %s\n", addr->address, addr->message);
    }


return TRUE;
}
