CURLMsg *curl_multi_info_read(struct Curl_multi *multi, int *msgs_in_queue)
{
  struct Curl_message *msg;

  *msgs_in_queue = 0;

  if(GOOD_MULTI_HANDLE(multi) && Curl_llist_count(multi->msglist)) {

    struct curl_llist_element *e;


    e = multi->msglist->head;

    msg = e->ptr;


    Curl_llist_remove(multi->msglist, e, NULL);

    *msgs_in_queue = curlx_uztosi(Curl_llist_count(multi->msglist));

    return &msg->extmsg;
  }
  else
    return NULL;
}
