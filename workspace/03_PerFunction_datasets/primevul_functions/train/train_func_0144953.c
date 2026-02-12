static void singlesocket(struct Curl_multi *multi,
                         struct Curl_easy *data)
{
  curl_socket_t socks[MAX_SOCKSPEREASYHANDLE];
  int i;
  struct Curl_sh_entry *entry;
  curl_socket_t s;
  int num;
  unsigned int curraction;

  for(i=0; i< MAX_SOCKSPEREASYHANDLE; i++)
    socks[i] = CURL_SOCKET_BAD;


  curraction = multi_getsock(data, socks, MAX_SOCKSPEREASYHANDLE);


  for(i=0; (i< MAX_SOCKSPEREASYHANDLE) &&
        (curraction & (GETSOCK_READSOCK(i) | GETSOCK_WRITESOCK(i)));
      i++) {
    int action = CURL_POLL_NONE;

    s = socks[i];


    entry = sh_getentry(&multi->sockhash, s);

    if(curraction & GETSOCK_READSOCK(i))
      action |= CURL_POLL_IN;
    if(curraction & GETSOCK_WRITESOCK(i))
      action |= CURL_POLL_OUT;

    if(entry) {

      if(entry->action == action)

        continue;
    }
    else {

      entry = sh_addentry(&multi->sockhash, s, data);
      if(!entry)

        return;
    }


    if(multi->socket_cb)
      multi->socket_cb(data,
                       s,
                       action,
                       multi->socket_userp,
                       entry->socketp);

    entry->action = action;
  }

  num = i;


  for(i=0; i< data->numsocks; i++) {
    int j;
    s = data->sockets[i];
    for(j=0; j<num; j++) {
      if(s == socks[j]) {

        s = CURL_SOCKET_BAD;
        break;
      }
    }

    entry = sh_getentry(&multi->sockhash, s);
    if(entry) {

      bool remove_sock_from_hash = TRUE;


      struct connectdata *easy_conn = data->easy_conn;
      if(easy_conn) {
        if(easy_conn->recv_pipe && easy_conn->recv_pipe->size > 1) {

          remove_sock_from_hash = FALSE;


          if(entry->easy == data) {
            if(Curl_recvpipe_head(data, easy_conn))
              entry->easy = easy_conn->recv_pipe->head->next->ptr;
            else
              entry->easy = easy_conn->recv_pipe->head->ptr;
          }
        }
        if(easy_conn->send_pipe  && easy_conn->send_pipe->size > 1) {

          remove_sock_from_hash = FALSE;


          if(entry->easy == data) {
            if(Curl_sendpipe_head(data, easy_conn))
              entry->easy = easy_conn->send_pipe->head->next->ptr;
            else
              entry->easy = easy_conn->send_pipe->head->ptr;
          }
        }


      }

      if(remove_sock_from_hash) {

        if(multi->socket_cb)
          multi->socket_cb(data,
                           s,
                           CURL_POLL_REMOVE,
                           multi->socket_userp,
                           entry->socketp);
        sh_delentry(&multi->sockhash, s);
      }
    }
  }

  memcpy(data->sockets, socks, num*sizeof(curl_socket_t));
  data->numsocks = num;
}
