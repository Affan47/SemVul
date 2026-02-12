CURLcode Curl_fillreadbuffer(struct Curl_easy *data, size_t bytes,
                             size_t *nreadp)
{
  size_t buffersize = bytes;
  size_t nread;

  curl_read_callback readfunc = NULL;
  void *extra_data = NULL;

#ifdef CURL_DOES_CONVERSIONS
  bool sending_http_headers = FALSE;
  struct connectdata *conn = data->conn;

  if(conn->handler->protocol&(PROTO_FAMILY_HTTP|CURLPROTO_RTSP)) {
    const struct HTTP *http = data->req.p.http;

    if(http->sending == HTTPSEND_REQUEST)


      sending_http_headers = TRUE;
  }
#endif

#ifndef CURL_DISABLE_HTTP
  if(data->state.trailers_state == TRAILERS_INITIALIZED) {
    struct curl_slist *trailers = NULL;
    CURLcode result;
    int trailers_ret_code;


    infof(data,
          "Moving trailers state machine from initialized to sending.\n");
    data->state.trailers_state = TRAILERS_SENDING;
    Curl_dyn_init(&data->state.trailers_buf, DYN_TRAILERS);

    data->state.trailers_bytes_sent = 0;
    Curl_set_in_callback(data, true);
    trailers_ret_code = data->set.trailer_callback(&trailers,
                                                   data->set.trailer_data);
    Curl_set_in_callback(data, false);
    if(trailers_ret_code == CURL_TRAILERFUNC_OK) {
      result = Curl_http_compile_trailers(trailers, &data->state.trailers_buf,
                                          data);
    }
    else {
      failf(data, "operation aborted by trailing headers callback");
      *nreadp = 0;
      result = CURLE_ABORTED_BY_CALLBACK;
    }
    if(result) {
      Curl_dyn_free(&data->state.trailers_buf);
      curl_slist_free_all(trailers);
      return result;
    }
    infof(data, "Successfully compiled trailers.\r\n");
    curl_slist_free_all(trailers);
  }
#endif


  if(data->req.upload_chunky &&
     data->state.trailers_state == TRAILERS_NONE) {

    buffersize -= (8 + 2 + 2);
    data->req.upload_fromhere += (8 + 2);
  }

#ifndef CURL_DISABLE_HTTP
  if(data->state.trailers_state == TRAILERS_SENDING) {


    readfunc = trailers_read;
    extra_data = (void *)data;
  }
  else
#endif
  {
    readfunc = data->state.fread_func;
    extra_data = data->state.in;
  }

  Curl_set_in_callback(data, true);
  nread = readfunc(data->req.upload_fromhere, 1,
                   buffersize, extra_data);
  Curl_set_in_callback(data, false);

  if(nread == CURL_READFUNC_ABORT) {
    failf(data, "operation aborted by callback");
    *nreadp = 0;
    return CURLE_ABORTED_BY_CALLBACK;
  }
  if(nread == CURL_READFUNC_PAUSE) {
    struct SingleRequest *k = &data->req;

    if(data->conn->handler->flags & PROTOPT_NONETWORK) {


      failf(data, "Read callback asked for PAUSE when not supported!");
      return CURLE_READ_ERROR;
    }


    k->keepon |= KEEP_SEND_PAUSE;
    if(data->req.upload_chunky) {

      data->req.upload_fromhere -= (8 + 2);
    }
    *nreadp = 0;

    return CURLE_OK;
  }
  else if(nread > buffersize) {

    *nreadp = 0;
    failf(data, "read function returned funny value");
    return CURLE_READ_ERROR;
  }

  if(!data->req.forbidchunk && data->req.upload_chunky) {


    bool added_crlf = FALSE;
    int hexlen = 0;
    const char *endofline_native;
    const char *endofline_network;

    if(
#ifdef CURL_DO_LINEEND_CONV
       (data->state.prefer_ascii) ||
#endif
       (data->set.crlf)) {

      endofline_native  = "\n";
      endofline_network = "\x0a";
    }
    else {
      endofline_native  = "\r\n";
      endofline_network = "\x0d\x0a";
    }


    if(data->state.trailers_state != TRAILERS_SENDING) {
      char hexbuffer[11] = "";
      hexlen = msnprintf(hexbuffer, sizeof(hexbuffer),
                         "%zx%s", nread, endofline_native);


      data->req.upload_fromhere -= hexlen;
      nread += hexlen;


      memcpy(data->req.upload_fromhere, hexbuffer, hexlen);


#ifndef CURL_DISABLE_HTTP
      if((nread-hexlen) == 0 &&
          data->set.trailer_callback != NULL &&
          data->state.trailers_state == TRAILERS_NONE) {
        data->state.trailers_state = TRAILERS_INITIALIZED;
      }
      else
#endif
      {
        memcpy(data->req.upload_fromhere + nread,
               endofline_network,
               strlen(endofline_network));
        added_crlf = TRUE;
      }
    }

#ifdef CURL_DOES_CONVERSIONS
    {
      CURLcode result;
      size_t length;
      if(data->state.prefer_ascii)

        length = nread;
      else

        length = hexlen;
      if(length) {
        result = Curl_convert_to_network(data, data->req.upload_fromhere,
                                         length);

        if(result)
          return result;
      }
    }
#endif

#ifndef CURL_DISABLE_HTTP
    if(data->state.trailers_state == TRAILERS_SENDING &&
       !trailers_left(data)) {
      Curl_dyn_free(&data->state.trailers_buf);
      data->state.trailers_state = TRAILERS_DONE;
      data->set.trailer_data = NULL;
      data->set.trailer_callback = NULL;

      data->req.upload_done = TRUE;
      infof(data, "Signaling end of chunked upload after trailers.\n");
    }
    else
#endif
      if((nread - hexlen) == 0 &&
         data->state.trailers_state != TRAILERS_INITIALIZED) {

        data->req.upload_done = TRUE;
        infof(data,
              "Signaling end of chunked upload via terminating chunk.\n");
      }

    if(added_crlf)
      nread += strlen(endofline_network);
  }
#ifdef CURL_DOES_CONVERSIONS
  else if((data->state.prefer_ascii) && (!sending_http_headers)) {
    CURLcode result;
    result = Curl_convert_to_network(data, data->req.upload_fromhere, nread);

    if(result)
      return result;
  }
#endif

  *nreadp = nread;

  return CURLE_OK;
}
