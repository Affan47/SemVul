transport_headers_send(transport_ctx * tctx,
  BOOL (*sendfn)(transport_ctx * tctx, uschar * s, int len))
{
header_line *h;
const uschar *list;
transport_instance * tblock = tctx ? tctx->tblock : NULL;
address_item * addr = tctx ? tctx->addr : NULL;


for (h = header_list; h; h = h->next) if (h->type != htype_old)
  {
  int i;
  BOOL include_header = TRUE;

  list = tblock ? tblock->remove_headers : NULL;
  for (i = 0; i < 2; i++)
    {
    if (list)
      {
      int sep = ':';
      uschar *s, *ss;
      while ((s = string_nextinlist(&list, &sep, NULL, 0)))
	{
	int len;

	if (i == 0)
	  if (!(s = expand_string(s)) && !f.expand_string_forcedfail)
	    {
	    errno = ERRNO_CHHEADER_FAIL;
	    return FALSE;
	    }
	len = s ? Ustrlen(s) : 0;
	if (strncmpic(h->text, s, len) != 0) continue;
	ss = h->text + len;
	while (*ss == ' ' || *ss == '\t') ss++;
	if (*ss == ':') break;
	}
      if (s) { include_header = FALSE; break; }
      }
    if (addr) list = addr->prop.remove_headers;
    }


  if (include_header)
    {
    if (tblock && tblock->rewrite_rules)
      {
      void *reset_point = store_get(0);
      header_line *hh;

      if ((hh = rewrite_header(h, NULL, NULL, tblock->rewrite_rules,
		  tblock->rewrite_existflags, FALSE)))
	{
	if (!sendfn(tctx, hh->text, hh->slen)) return FALSE;
	store_reset(reset_point);
	continue;
	}
      }


    if (!sendfn(tctx, h->text, h->slen)) return FALSE;
    }


  else
    DEBUG(D_transport) debug_printf("removed header line:\n%s---\n", h->text);
  }


if (addr)
  {
  int i;
  header_line *hprev = addr->prop.extra_headers;
  header_line *hnext;
  for (i = 0; i < 2; i++)
    for (h = hprev, hprev = NULL; h; h = hnext)
      {
      hnext = h->next;
      h->next = hprev;
      hprev = h;
      if (i == 1)
	{
	if (!sendfn(tctx, h->text, h->slen)) return FALSE;
	DEBUG(D_transport)
	  debug_printf("added header line(s):\n%s---\n", h->text);
	}
      }
  }


if (tblock && (list = CUS tblock->add_headers))
  {
  int sep = '\n';
  uschar * s;

  while ((s = string_nextinlist(&list, &sep, NULL, 0)))
    if ((s = expand_string(s)))
      {
      int len = Ustrlen(s);
      if (len > 0)
	{
	if (!sendfn(tctx, s, len)) return FALSE;
	if (s[len-1] != '\n' && !sendfn(tctx, US"\n", 1))
	  return FALSE;
	DEBUG(D_transport)
	  {
	  debug_printf("added header line:\n%s", s);
	  if (s[len-1] != '\n') debug_printf("\n");
	  debug_printf("---\n");
	  }
	}
      }
    else if (!f.expand_string_forcedfail)
      { errno = ERRNO_CHHEADER_FAIL; return FALSE; }
  }


return sendfn(tctx, US"\n", 1);
}
