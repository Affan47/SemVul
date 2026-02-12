void Curl_expire(struct Curl_easy *data, long milli)
{
  struct Curl_multi *multi = data->multi;
  struct timeval *nowp = &data->state.expiretime;
  int rc;


  if(!multi)
    return;

  if(!milli) {

    if(nowp->tv_sec || nowp->tv_usec) {


      struct curl_llist *list = data->state.timeoutlist;

      rc = Curl_splayremovebyaddr(multi->timetree,
                                  &data->state.timenode,
                                  &multi->timetree);
      if(rc)
        infof(data, "Internal error clearing splay node = %d\n", rc);


      while(list->size > 0)
        Curl_llist_remove(list, list->tail, NULL);

#ifdef DEBUGBUILD
      infof(data, "Expire cleared\n");
#endif
      nowp->tv_sec = 0;
      nowp->tv_usec = 0;
    }
  }
  else {
    struct timeval set;

    set = Curl_tvnow();
    set.tv_sec += milli/1000;
    set.tv_usec += (milli%1000)*1000;

    if(set.tv_usec >= 1000000) {
      set.tv_sec++;
      set.tv_usec -= 1000000;
    }

    if(nowp->tv_sec || nowp->tv_usec) {


      long diff = curlx_tvdiff(set, *nowp);
      if(diff > 0) {


        multi_addtimeout(data->state.timeoutlist, &set);
        return;
      }


      multi_addtimeout(data->state.timeoutlist, nowp);


      rc = Curl_splayremovebyaddr(multi->timetree,
                                  &data->state.timenode,
                                  &multi->timetree);
      if(rc)
        infof(data, "Internal error removing splay node = %d\n", rc);
    }

    *nowp = set;
    data->state.timenode.payload = data;
    multi->timetree = Curl_splayinsert(*nowp,
                                       multi->timetree,
                                       &data->state.timenode);
  }
#if 0
  Curl_splayprint(multi->timetree, 0, TRUE);
#endif
}
