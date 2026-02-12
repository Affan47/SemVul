write_chunk(transport_ctx * tctx, uschar *chunk, int len)
{
uschar *start = chunk;
uschar *end = chunk + len;
uschar *ptr;
int mlen = DELIVER_OUT_BUFFER_SIZE - nl_escape_length - 2;


if (nl_partial_match >= 0)
  {
  if (nl_check_length > 0 && len >= nl_check_length &&
      Ustrncmp(start, nl_check + nl_partial_match,
        nl_check_length - nl_partial_match) == 0)
    {
    Ustrncpy(chunk_ptr, nl_escape, nl_escape_length);
    chunk_ptr += nl_escape_length;
    start += nl_check_length - nl_partial_match;
    }


  else if (nl_partial_match > 0)
    {
    Ustrncpy(chunk_ptr, nl_check, nl_partial_match);
    chunk_ptr += nl_partial_match;
    }

  nl_partial_match = -1;
  }


for (ptr = start; ptr < end; ptr++)
  {
  int ch, len;


  if ((len = chunk_ptr - deliver_out_buffer) > mlen)
    {
    DEBUG(D_transport) debug_printf("flushing headers buffer\n");


    if (tctx->options & topt_use_bdat  &&  tctx->chunk_cb)
      {
      if (  tctx->chunk_cb(tctx, (unsigned)len, 0) != OK
	 || !transport_write_block(tctx, deliver_out_buffer, len, FALSE)
	 || tctx->chunk_cb(tctx, 0, tc_reap_prev) != OK
	 )
	return FALSE;
      }
    else
      if (!transport_write_block(tctx, deliver_out_buffer, len, FALSE))
	return FALSE;
    chunk_ptr = deliver_out_buffer;
    }


  if (  *ptr == '\r' && ptr[1] == '\n'
     && !(tctx->options & topt_use_crlf)
     && f.spool_file_wireformat
     )
    ptr++;

  if ((ch = *ptr) == '\n')
    {
    int left = end - ptr - 1;


    if (tctx->options & topt_use_crlf && !f.spool_file_wireformat)
      *chunk_ptr++ = '\r';
    *chunk_ptr++ = '\n';
    transport_newlines++;


    if (nl_check_length > 0)
      {
      if (left >= nl_check_length &&
          Ustrncmp(ptr+1, nl_check, nl_check_length) == 0)
        {
        Ustrncpy(chunk_ptr, nl_escape, nl_escape_length);
        chunk_ptr += nl_escape_length;
        ptr += nl_check_length;
        }


      else if (left <= 0) nl_partial_match = 0;

      else if (Ustrncmp(ptr+1, nl_check, left) == 0)
        {
        nl_partial_match = left;
        ptr = end;
        }
      }
    }


  else *chunk_ptr++ = ch;
  }

return TRUE;
}
