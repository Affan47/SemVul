parse_headers (Call *c, char **bufp, size_t *buf_lenp)
{
  char *hdr, *buf_start = *bufp;
  Conn *s = c->conn;
  size_t hdr_len;
  Any_Type arg;

  while (get_line (c, bufp, buf_lenp) > 0)
    {
      hdr = s->line.iov_base;
      hdr_len = s->line.iov_len;

      if (!hdr_len)
	{

	  if (s->has_body)
	    if (s->is_chunked)
	      {
		s->content_length = 0;
		s->state = S_REPLY_CHUNKED;
	      }
	    else
	      s->state = S_REPLY_DATA;
	  else if (s->state == S_REPLY_CONTINUE)
	    s->state = S_REPLY_HEADER;
	  else
	    s->state = S_REPLY_DONE;
	  break;
	}


      switch (tolower (*hdr))
	{
	case 'c':
	  if (strncasecmp (hdr, "content-length:", 15) == 0)
	    {
	      hdr += 15;
	      s->content_length = strtoul (hdr, 0, 10);
	      if (!s->content_length)
	    s->has_body = 0;
	    }
	  break;

	case 't':
	  if (strncasecmp (hdr, "transfer-encoding:", 18) == 0)
	    {
	      hdr += 18;
	      while (isspace (*hdr))
		++hdr;
	      if (strcasecmp (hdr, "chunked") == 0)
		s->is_chunked = 1;
	      else
		fprintf (stderr, "%s.parse_headers: unknown transfer "
			 "encoding `%s'\n", prog_name, hdr);
	    }
	  break;
	}
      arg.vp = &s->line;
      event_signal (EV_CALL_RECV_HDR, (Object *) c, arg);
      if (s->state >= S_CLOSING)
	return;
      s->line.iov_len = 0;
    }
  c->reply.header_bytes += *bufp - buf_start;
}
