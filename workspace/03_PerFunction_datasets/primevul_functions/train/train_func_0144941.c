void Curl_multi_closed(struct connectdata *conn, curl_socket_t s)
{
  struct Curl_multi *multi = conn->data->multi;
  if(multi) {


    struct Curl_sh_entry *entry = sh_getentry(&multi->sockhash, s);

    if(entry) {
      if(multi->socket_cb)
        multi->socket_cb(conn->data, s, CURL_POLL_REMOVE,
                         multi->socket_userp,
                         entry->socketp);


      sh_delentry(&multi->sockhash, s);
    }
  }
}
