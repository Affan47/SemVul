adns__search_next(adns_state ads, adns_query qu, struct timeval now) {
  const char *nextentry;
  adns_status stat;

  if (qu->search_doneabs<0) {
    nextentry= 0;
    qu->search_doneabs= 1;
  } else {
    if (qu->search_pos >= ads->nsearchlist) {
      if (qu->search_doneabs) {
	qu->search_vb.used= qu->search_origlen;
	stat= adns_s_nxdomain; goto x_fail;
      } else {
	nextentry= 0;
	qu->search_doneabs= 1;
      }
    } else {
      nextentry= ads->searchlist[qu->search_pos++];
    }
  }

  qu->search_vb.used= qu->search_origlen;
  if (nextentry) {
    if (!adns__vbuf_append(&qu->search_vb,".",1) ||
	!adns__vbuf_appendstr(&qu->search_vb,nextentry))
      goto x_nomemory;
  }

  free(qu->query_dgram);
  qu->query_dgram= 0; qu->query_dglen= 0;

  query_simple(ads,qu, qu->search_vb.buf, qu->search_vb.used,
	       qu->typei, qu->flags, now);
  return;

x_nomemory:
  stat= adns_s_nomemory;
x_fail:
  adns__query_fail(qu,stat);
}
