CURLMcode curl_multi_remove_handle(struct Curl_multi *multi,
                                   struct Curl_easy *data)
{
  struct Curl_easy *easy = data;
  bool premature;
  bool easy_owns_conn;
  struct curl_llist_element *e;


  if(!GOOD_MULTI_HANDLE(multi))
    return CURLM_BAD_HANDLE;


  if(!GOOD_EASY_HANDLE(data))
    return CURLM_BAD_EASY_HANDLE;


  if(!data->multi)
    return CURLM_OK;

  premature = (data->mstate < CURLM_STATE_COMPLETED) ? TRUE : FALSE;
  easy_owns_conn = (data->easy_conn && (data->easy_conn->data == easy)) ?
    TRUE : FALSE;


  if(premature) {


    multi->num_alive--;


    Curl_multi_process_pending_handles(multi);
  }

  if(data->easy_conn &&
     data->mstate > CURLM_STATE_DO &&
     data->mstate < CURLM_STATE_COMPLETED) {


    connclose(data->easy_conn, "Removed with partial response");


    data->easy_conn->data = easy;
    easy_owns_conn = TRUE;
  }


  Curl_expire(data, 0);

  if(data->dns.hostcachetype == HCACHE_MULTI) {

    data->dns.hostcache = NULL;
    data->dns.hostcachetype = HCACHE_NONE;
  }

  if(data->easy_conn) {


    if(easy_owns_conn) {


      (void)multi_done(&data->easy_conn, data->result, premature);
    }
    else

      Curl_getoff_all_pipelines(data, data->easy_conn);
  }

  Curl_wildcard_dtor(&data->wildcard);


  if(data->state.timeoutlist) {
    Curl_llist_destroy(data->state.timeoutlist, NULL);
    data->state.timeoutlist = NULL;
  }


  data->state.conn_cache = NULL;


  data->mstate = CURLM_STATE_COMPLETED;
  singlesocket(multi, easy);


  if(data->easy_conn) {
    data->easy_conn->data = NULL;
    data->easy_conn = NULL;
  }

  data->multi = NULL;


  for(e = multi->msglist->head; e; e = e->next) {
    struct Curl_message *msg = e->ptr;

    if(msg->extmsg.easy_handle == easy) {
      Curl_llist_remove(multi->msglist, e, NULL);

      break;
    }
  }


  if(data->prev)
    data->prev->next = data->next;
  else
    multi->easyp = data->next;


  if(data->next)
    data->next->prev = data->prev;
  else
    multi->easylp = data->prev;


  multi->num_easy--;

  update_timer(multi);
  return CURLM_OK;
}
