internal_transport_write_message(transport_ctx * tctx, int size_limit)
{
int len, size = 0;


transport_write_reset(tctx->options);


if (tctx->check_string && tctx->escape_string)
  {
  nl_check = tctx->check_string;
  nl_check_length = Ustrlen(nl_check);
  nl_escape = tctx->escape_string;
  nl_escape_length = Ustrlen(nl_escape);
  }


if (!(tctx->options & topt_escape_headers))
  nl_check_length = -nl_check_length;


if (!(tctx->options & topt_no_headers))
  {
  BOOL save_wireformat = f.spool_file_wireformat;
  f.spool_file_wireformat = FALSE;


  if (tctx->options & topt_add_return_path)
    {
    uschar buffer[ADDRESS_MAXLENGTH + 20];
    int n = sprintf(CS buffer, "Return-path: <%.*s>\n", ADDRESS_MAXLENGTH,
      return_path);
    if (!write_chunk(tctx, buffer, n)) goto bad;
    }


  if (tctx->options & topt_add_envelope_to)
    {
    BOOL first = TRUE;
    address_item *p;
    struct aci *plist = NULL;
    struct aci *dlist = NULL;
    void *reset_point = store_get(0);

    if (!write_chunk(tctx, US"Envelope-to: ", 13)) goto bad;


    for (p = tctx->addr; p; p = p->next)
      if (!write_env_to(p, &plist, &dlist, &first, tctx)) goto bad;


    if (!write_chunk(tctx, US"\n", 1)) goto bad;
    store_reset(reset_point);
    }


  if (tctx->options & topt_add_delivery_date)
    {
    uschar * s = tod_stamp(tod_full);

    if (  !write_chunk(tctx, US"Delivery-date: ", 15)
       || !write_chunk(tctx, s, Ustrlen(s))
       || !write_chunk(tctx, US"\n", 1)) goto bad;
    }


  if (!transport_headers_send(tctx, &write_chunk))
    {
bad:
    f.spool_file_wireformat = save_wireformat;
    return FALSE;
    }

  f.spool_file_wireformat = save_wireformat;
  }


if (tctx->options & topt_use_bdat)
  {
  off_t fsize;
  int hsize;

  if ((hsize = chunk_ptr - deliver_out_buffer) < 0)
    hsize = 0;
  if (!(tctx->options & topt_no_body))
    {
    if ((fsize = lseek(deliver_datafile, 0, SEEK_END)) < 0) return FALSE;
    fsize -= SPOOL_DATA_START_OFFSET;
    if (size_limit > 0  &&  fsize > size_limit)
      fsize = size_limit;
    size = hsize + fsize;
    if (tctx->options & topt_use_crlf  &&  !f.spool_file_wireformat)
      size += body_linecount;


    }


  if (size > DELIVER_OUT_BUFFER_SIZE && hsize > 0)
    {
    DEBUG(D_transport)
      debug_printf("sending small initial BDAT; hsize=%d\n", hsize);
    if (  tctx->chunk_cb(tctx, hsize, 0) != OK
       || !transport_write_block(tctx, deliver_out_buffer, hsize, FALSE)
       || tctx->chunk_cb(tctx, 0, tc_reap_prev) != OK
       )
      return FALSE;
    chunk_ptr = deliver_out_buffer;
    size -= hsize;
    }


  if (tctx->chunk_cb(tctx, size, tc_chunk_last) != OK)
    return FALSE;
  tctx->options &= ~topt_use_bdat;
  }


#ifdef OS_SENDFILE
if (  f.spool_file_wireformat
   && !(tctx->options & (topt_no_body | topt_end_dot))
   && !nl_check_length
   && tls_out.active.sock != tctx->u.fd
   )
  {
  ssize_t copied = 0;
  off_t offset = SPOOL_DATA_START_OFFSET;


  if ((len = chunk_ptr - deliver_out_buffer) > 0)
    {
    if (!transport_write_block(tctx, deliver_out_buffer, len, TRUE))
      return FALSE;
    size -= len;
    }

  DEBUG(D_transport) debug_printf("using sendfile for body\n");

  while(size > 0)
    {
    if ((copied = os_sendfile(tctx->u.fd, deliver_datafile, &offset, size)) <= 0) break;
    size -= copied;
    }
  return copied >= 0;
  }
#else
DEBUG(D_transport) debug_printf("cannot use sendfile for body: no support\n");
#endif

DEBUG(D_transport)
  if (!(tctx->options & topt_no_body))
    debug_printf("cannot use sendfile for body: %s\n",
      !f.spool_file_wireformat ? "spoolfile not wireformat"
      : tctx->options & topt_end_dot ? "terminating dot wanted"
      : nl_check_length ? "dot- or From-stuffing wanted"
      : "TLS output wanted");

if (!(tctx->options & topt_no_body))
  {
  int size = size_limit;

  nl_check_length = abs(nl_check_length);
  nl_partial_match = 0;
  if (lseek(deliver_datafile, SPOOL_DATA_START_OFFSET, SEEK_SET) < 0)
    return FALSE;
  while (  (len = MAX(DELIVER_IN_BUFFER_SIZE, size)) > 0
	&& (len = read(deliver_datafile, deliver_in_buffer, len)) > 0)
    {
    if (!write_chunk(tctx, deliver_in_buffer, len))
      return FALSE;
    size -= len;
    }


  if (len != 0) return FALSE;
  }


nl_check_length = nl_escape_length = 0;
f.spool_file_wireformat = FALSE;


if (tctx->options & topt_end_dot && !write_chunk(tctx, US".\n", 2))
  return FALSE;


return (len = chunk_ptr - deliver_out_buffer) <= 0 ||
  transport_write_block(tctx, deliver_out_buffer, len, FALSE);
}
