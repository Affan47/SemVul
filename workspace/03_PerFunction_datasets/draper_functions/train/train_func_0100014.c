add_buffer_send(send_buffer *in,
                         struct connectdata *conn,
                         long *bytes_written,

                         size_t included_body_bytes,

                         int socketindex)

{
  ssize_t amount;
  CURLcode res;
  char *ptr;
  size_t size;
  struct HTTP *http = conn->data->reqdata.proto.http;
  size_t sendsize;
  curl_socket_t sockfd;

  curlassert(socketindex <= SECONDARYSOCKET);

  sockfd = conn->sock[socketindex];


  ptr = in->buffer;
  size = in->size_used;

#ifdef CURL_DOES_CONVERSIONS
  if(size - included_body_bytes > 0) {
    res = Curl_convert_to_network(conn->data, ptr, size - included_body_bytes);

    if(res != CURLE_OK) {

      if(in->buffer)
        free(in->buffer);
      free(in);
      return res;
    }
  }
#endif

  if(conn->protocol & PROT_HTTPS) {


    sendsize= (size > CURL_MAX_WRITE_SIZE)?CURL_MAX_WRITE_SIZE:size;


    memcpy(conn->data->state.uploadbuffer, ptr, sendsize);
    ptr = conn->data->state.uploadbuffer;
  }
  else
    sendsize = size;

  res = Curl_write(conn, sockfd, ptr, sendsize, &amount);

  if(CURLE_OK == res) {

    if(conn->data->set.verbose) {

      Curl_debug(conn->data, CURLINFO_HEADER_OUT, ptr,
                 (size_t)(amount-included_body_bytes), conn);
      if (included_body_bytes)
        Curl_debug(conn->data, CURLINFO_DATA_OUT,
                   ptr+amount-included_body_bytes,
                   (size_t)included_body_bytes, conn);
    }

    *bytes_written += amount;

    if(http) {
      if((size_t)amount != size) {


        size -= amount;

        ptr = in->buffer + amount;


        http->backup.fread = conn->fread;
        http->backup.fread_in = conn->fread_in;
        http->backup.postdata = http->postdata;
        http->backup.postsize = http->postsize;


        conn->fread = (curl_read_callback)readmoredata;
        conn->fread_in = (void *)conn;
        http->postdata = ptr;
        http->postsize = (curl_off_t)size;

        http->send_buffer = in;
        http->sending = HTTPSEND_REQUEST;

        return CURLE_OK;
      }
      http->sending = HTTPSEND_BODY;

    }
    else {
      if((size_t)amount != size)


        return CURLE_SEND_ERROR;
      else
        conn->writechannel_inuse = FALSE;
    }
  }
  if(in->buffer)
    free(in->buffer);
  free(in);

  return res;
}
