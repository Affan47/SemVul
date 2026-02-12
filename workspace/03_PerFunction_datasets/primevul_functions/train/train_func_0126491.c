header_add_backend(BOOL after, uschar *name, BOOL topnot, int type,
  const char *format, va_list ap)
{
header_line *h, *new;
header_line **hptr;

uschar *p, *q;
uschar buffer[HEADER_ADD_BUFFER_SIZE];
gstring gs = { .size = HEADER_ADD_BUFFER_SIZE, .ptr = 0, .s = buffer };

if (!header_last) return;

if (!string_vformat(&gs, FALSE, format, ap))
  log_write(0, LOG_MAIN|LOG_PANIC_DIE, "string too long in header_add: "
    "%.100s ...", string_from_gstring(&gs));
string_from_gstring(&gs);


if (!name)
  {
  if (after)
    {
    hptr = &(header_last->next);
    h = NULL;
    }
  else
    {
    hptr = &header_list;


    if (!header_list->text)
      hptr = &header_list->next;
    h = *hptr;
    }
  }

else
  {
  int len = Ustrlen(name);


  for (hptr = &header_list; (h = *hptr); hptr = &h->next)
    if (header_testname(h, name, len, TRUE))
      break;


  if (!h)
    {
    if (topnot)
      {
      hptr = &header_list;
      h = header_list;
      }
    }


  else if (after)
    for (;;)
      {
      if (!h->next || !header_testname(h, name, len, FALSE)) break;
      hptr = &(h->next);
      h = h->next;
      }
  }


for (p = q = buffer; *p != 0; )
  {
  for (;;)
    {
    q = Ustrchr(q, '\n');
    if (!q) q = p + Ustrlen(p);
    if (*(++q) != ' ' && *q != '\t') break;
    }

  new = store_get(sizeof(header_line));
  new->text = string_copyn(p, q - p);
  new->slen = q - p;
  new->type = type;
  new->next = h;

  *hptr = new;
  hptr = &(new->next);

  if (!h) header_last = new;
  p = q;
  }
}
