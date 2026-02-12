CURLMcode curl_multi_add_handle(struct Curl_multi *multi,
                                struct Curl_easy *data)
{
  struct curl_llist *timeoutlist;


  if(!GOOD_MULTI_HANDLE(multi))
    return CURLM_BAD_HANDLE;


  if(!GOOD_EASY_HANDLE(data))
    return CURLM_BAD_EASY_HANDLE;


  if(data->multi)
    return CURLM_ADDED_ALREADY;


  timeoutlist = Curl_llist_alloc(multi_freetimeout);
  if(!timeoutlist)
    return CURLM_OUT_OF_MEMORY;


  data->state.timeoutlist = timeoutlist;
  timeoutlist = NULL;


  multistate(data, CURLM_STATE_INIT);

  if((data->set.global_dns_cache) &&
     (data->dns.hostcachetype != HCACHE_GLOBAL)) {

    struct curl_hash *global = Curl_global_host_cache_init();
    if(global) {

      data->dns.hostcache = global;
      data->dns.hostcachetype = HCACHE_GLOBAL;
    }
  }


  else if(!data->dns.hostcache ||
     (data->dns.hostcachetype == HCACHE_NONE)) {
    data->dns.hostcache = &multi->hostcache;
    data->dns.hostcachetype = HCACHE_MULTI;
  }


  data->state.conn_cache = &multi->conn_cache;


  data->next = NULL;
  if(multi->easyp) {
    struct Curl_easy *last = multi->easylp;
    last->next = data;
    data->prev = last;
    multi->easylp = data;
  }
  else {

    data->prev = NULL;
    multi->easylp = multi->easyp = data;
  }


  data->multi = multi;


  Curl_expire(data, 1);


  multi->num_easy++;


  multi->num_alive++;


  memset(&multi->timer_lastcall, 0, sizeof(multi->timer_lastcall));

  update_timer(multi);
  return CURLM_OK;
}
