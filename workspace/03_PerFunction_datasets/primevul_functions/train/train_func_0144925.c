static CURLMcode add_next_timeout(struct timeval now,
                                  struct Curl_multi *multi,
                                  struct Curl_easy *d)
{
  struct timeval *tv = &d->state.expiretime;
  struct curl_llist *list = d->state.timeoutlist;
  struct curl_llist_element *e;


  for(e = list->head; e;) {
    struct curl_llist_element *n = e->next;
    long diff = curlx_tvdiff(*(struct timeval *)e->ptr, now);
    if(diff <= 0)

      Curl_llist_remove(list, e, NULL);
    else

      break;
    e = n;
  }
  e = list->head;
  if(!e) {


    tv->tv_sec = 0;
    tv->tv_usec = 0;
  }
  else {

    memcpy(tv, e->ptr, sizeof(*tv));


    Curl_llist_remove(list, e, NULL);


    multi->timetree = Curl_splayinsert(*tv, multi->timetree,
                                       &d->state.timenode);
  }
  return CURLM_OK;
}
