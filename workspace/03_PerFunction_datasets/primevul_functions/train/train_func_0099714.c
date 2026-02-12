static CURLcode tftp_send_first(tftp_state_data_t *state, tftp_event_t event)
{
  size_t sbytes;
  ssize_t senddata;
  const char *mode = "octet";
  char *filename;
  struct Curl_easy *data = state->conn->data;
  CURLcode result = CURLE_OK;


  if(data->set.prefer_ascii)
    mode = "netascii";

  switch(event) {

  case TFTP_EVENT_INIT:
  case TFTP_EVENT_TIMEOUT:

    state->retries++;
    if(state->retries>state->retry_max) {
      state->error = TFTP_ERR_NORESPONSE;
      state->state = TFTP_STATE_FIN;
      return result;
    }

    if(data->set.upload) {

      setpacketevent(&state->spacket, TFTP_EVENT_WRQ);
      state->conn->data->req.upload_fromhere =
        (char *)state->spacket.data + 4;
      if(data->state.infilesize != -1)
        Curl_pgrsSetUploadSize(data, data->state.infilesize);
    }
    else {

      setpacketevent(&state->spacket, TFTP_EVENT_RRQ);
    }


    result = Curl_urldecode(data, &state->conn->data->state.up.path[1], 0,
                            &filename, NULL, FALSE);
    if(result)
      return result;

    if(strlen(filename) > (state->blksize - strlen(mode) - 4)) {
      failf(data, "TFTP file name too long\n");
      free(filename);
      return CURLE_TFTP_ILLEGAL;
    }

    msnprintf((char *)state->spacket.data + 2,
              state->blksize,
              "%s%c%s%c", filename, '\0',  mode, '\0');
    sbytes = 4 + strlen(filename) + strlen(mode);


    if(!data->set.tftp_no_options) {
      char buf[64];

      if(data->set.upload && (data->state.infilesize != -1))
        msnprintf(buf, sizeof(buf), "%" CURL_FORMAT_CURL_OFF_T,
                  data->state.infilesize);
      else
        strcpy(buf, "0");

      result = tftp_option_add(state, &sbytes,
                               (char *)state->spacket.data + sbytes,
                               TFTP_OPTION_TSIZE);
      if(result == CURLE_OK)
        result = tftp_option_add(state, &sbytes,
                                 (char *)state->spacket.data + sbytes, buf);


      msnprintf(buf, sizeof(buf), "%d", state->requested_blksize);
      if(result == CURLE_OK)
        result = tftp_option_add(state, &sbytes,
                                 (char *)state->spacket.data + sbytes,
                                 TFTP_OPTION_BLKSIZE);
      if(result == CURLE_OK)
        result = tftp_option_add(state, &sbytes,
                                 (char *)state->spacket.data + sbytes, buf);


      msnprintf(buf, sizeof(buf), "%d", state->retry_time);
      if(result == CURLE_OK)
        result = tftp_option_add(state, &sbytes,
                                 (char *)state->spacket.data + sbytes,
                                 TFTP_OPTION_INTERVAL);
      if(result == CURLE_OK)
        result = tftp_option_add(state, &sbytes,
                                 (char *)state->spacket.data + sbytes, buf);

      if(result != CURLE_OK) {
        failf(data, "TFTP buffer too small for options");
        free(filename);
        return CURLE_TFTP_ILLEGAL;
      }
    }


    senddata = sendto(state->sockfd, (void *)state->spacket.data,
                      (SEND_TYPE_ARG3)sbytes, 0,
                      state->conn->ip_addr->ai_addr,
                      state->conn->ip_addr->ai_addrlen);
    if(senddata != (ssize_t)sbytes) {
      char buffer[STRERROR_LEN];
      failf(data, "%s", Curl_strerror(SOCKERRNO, buffer, sizeof(buffer)));
    }
    free(filename);
    break;

  case TFTP_EVENT_OACK:
    if(data->set.upload) {
      result = tftp_connect_for_tx(state, event);
    }
    else {
      result = tftp_connect_for_rx(state, event);
    }
    break;

  case TFTP_EVENT_ACK:
    result = tftp_connect_for_tx(state, event);
    break;

  case TFTP_EVENT_DATA:
    result = tftp_connect_for_rx(state, event);
    break;

  case TFTP_EVENT_ERROR:
    state->state = TFTP_STATE_FIN;
    break;

  default:
    failf(state->conn->data, "tftp_send_first: internal error");
    break;
  }

  return result;
}
