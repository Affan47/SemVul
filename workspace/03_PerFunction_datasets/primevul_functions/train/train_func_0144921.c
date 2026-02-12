static CURLMcode multi_socket(struct Curl_multi *multi,
                              bool checkall,
                              curl_socket_t s,
                              int ev_bitmask,
                              int *running_handles)
{
  CURLMcode result = CURLM_OK;
  struct Curl_easy *data = NULL;
  struct Curl_tree *t;
  struct timeval now = Curl_tvnow();

  if(checkall) {

    result = curl_multi_perform(multi, running_handles);


    if(result != CURLM_BAD_HANDLE) {
      data=multi->easyp;
      while(data) {
        singlesocket(multi, data);
        data = data->next;
      }
    }


    return result;
  }
  else if(s != CURL_SOCKET_TIMEOUT) {

    struct Curl_sh_entry *entry = sh_getentry(&multi->sockhash, s);

    if(!entry)


      ;
    else {
      SIGPIPE_VARIABLE(pipe_st);

      data = entry->easy;

      if(data->magic != CURLEASY_MAGIC_NUMBER)

        return CURLM_INTERNAL_ERROR;


      if(data->easy_conn) {
        if((ev_bitmask & CURL_POLL_OUT) &&
           data->easy_conn->send_pipe &&
           data->easy_conn->send_pipe->head)
          data = data->easy_conn->send_pipe->head->ptr;
        else if((ev_bitmask & CURL_POLL_IN) &&
                data->easy_conn->recv_pipe &&
                data->easy_conn->recv_pipe->head)
          data = data->easy_conn->recv_pipe->head->ptr;
      }

      if(data->easy_conn &&
         !(data->easy_conn->handler->flags & PROTOPT_DIRLOCK))

        data->easy_conn->cselect_bits = ev_bitmask;

      sigpipe_ignore(data, &pipe_st);
      result = multi_runsingle(multi, now, data);
      sigpipe_restore(&pipe_st);

      if(data->easy_conn &&
         !(data->easy_conn->handler->flags & PROTOPT_DIRLOCK))

        data->easy_conn->cselect_bits = 0;

      if(CURLM_OK >= result)


        singlesocket(multi, data);


      data = NULL;

      now = Curl_tvnow();

    }
  }
  else {


    memset(&multi->timer_lastcall, 0, sizeof(multi->timer_lastcall));
  }


  do {

    if(data) {
      SIGPIPE_VARIABLE(pipe_st);

      sigpipe_ignore(data, &pipe_st);
      result = multi_runsingle(multi, now, data);
      sigpipe_restore(&pipe_st);

      if(CURLM_OK >= result)


        singlesocket(multi, data);
    }


    multi->timetree = Curl_splaygetbest(now, multi->timetree, &t);
    if(t) {
      data = t->payload;
      (void)add_next_timeout(now, multi, t->payload);
    }

  } while(t);

  *running_handles = multi->num_alive;
  return result;
}
