static CURLMcode multi_timeout(struct Curl_multi *multi,
                               long *timeout_ms)
{
  static struct timeval tv_zero = {0, 0};

  if(multi->timetree) {

    struct timeval now = Curl_tvnow();


    multi->timetree = Curl_splay(tv_zero, multi->timetree);

    if(Curl_splaycomparekeys(multi->timetree->key, now) > 0) {

      *timeout_ms = curlx_tvdiff(multi->timetree->key, now);
      if(!*timeout_ms)


        *timeout_ms=1;
    }
    else

      *timeout_ms = 0;
  }
  else
    *timeout_ms = -1;

  return CURLM_OK;
}
