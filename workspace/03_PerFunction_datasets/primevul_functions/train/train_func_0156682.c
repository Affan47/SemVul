host_build_hostlist(host_item **anchor, const uschar *list, BOOL randomize)
{
int sep = 0;
int fake_mx = MX_NONE;
uschar *name;

if (!list) return;
if (randomize) fake_mx--;

*anchor = NULL;

while ((name = string_nextinlist(&list, &sep, NULL, 0)))
  {
  host_item *h;

  if (name[0] == '+' && name[1] == 0)
    {
    if (randomize) fake_mx--;
    continue;
    }

  h = store_get(sizeof(host_item), FALSE);
  h->name = name;
  h->address = NULL;
  h->port = PORT_NONE;
  h->mx = fake_mx;
  h->sort_key = randomize? (-fake_mx)*1000 + random_number(1000) : 0;
  h->status = hstatus_unknown;
  h->why = hwhy_unknown;
  h->last_try = 0;

  if (!*anchor)
    {
    h->next = NULL;
    *anchor = h;
    }
  else
    {
    host_item *hh = *anchor;
    if (h->sort_key < hh->sort_key)
      {
      h->next = hh;
      *anchor = h;
      }
    else
      {
      while (hh->next && h->sort_key >= hh->next->sort_key)
        hh = hh->next;
      h->next = hh->next;
      hh->next = h;
      }
    }
  }
}
