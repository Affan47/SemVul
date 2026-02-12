static CURLcode tftp_tx(tftp_state_data_t *state, tftp_event_t event)
{
  struct Curl_easy *data = state->conn->data;
  ssize_t sbytes;
  CURLcode result = CURLE_OK;
  struct SingleRequest *k = &data->req;
  size_t cb;
  char buffer[STRERROR_LEN];

  switch(event) {

  case TFTP_EVENT_ACK:
  case TFTP_EVENT_OACK:
    if(event == TFTP_EVENT_ACK) {

      int rblock = getrpacketblock(&state->rpacket);

      if(rblock != state->block &&


         !(state->block == 0 && rblock == 65535)) {

        infof(data, "Received ACK for block %d, expecting %d\n",
              rblock, state->block);
        state->retries++;

        if(state->retries>state->retry_max) {
          failf(data, "tftp_tx: giving up waiting for block %d ack",
                state->block);
          result = CURLE_SEND_ERROR;
        }
        else {

          sbytes = sendto(state->sockfd, (void *)state->spacket.data,
                          4 + state->sbytes, SEND_4TH_ARG,
                          (struct sockaddr *)&state->remote_addr,
                          state->remote_addrlen);

          if(sbytes<0) {
            failf(data, "%s", Curl_strerror(SOCKERRNO,
                                            buffer, sizeof(buffer)));
            result = CURLE_SEND_ERROR;
          }
        }

        return result;
      }


      time(&state->rx_time);
      state->block++;
    }
    else
      state->block = 1;

    state->retries = 0;
    setpacketevent(&state->spacket, TFTP_EVENT_DATA);
    setpacketblock(&state->spacket, state->block);
    if(state->block > 1 && state->sbytes < state->blksize) {
      state->state = TFTP_STATE_FIN;
      return CURLE_OK;
    }


    state->sbytes = 0;
    state->conn->data->req.upload_fromhere = (char *)state->spacket.data + 4;
    do {
      result = Curl_fillreadbuffer(state->conn, state->blksize - state->sbytes,
                                   &cb);
      if(result)
        return result;
      state->sbytes += (int)cb;
      state->conn->data->req.upload_fromhere += cb;
    } while(state->sbytes < state->blksize && cb != 0);

    sbytes = sendto(state->sockfd, (void *) state->spacket.data,
                    4 + state->sbytes, SEND_4TH_ARG,
                    (struct sockaddr *)&state->remote_addr,
                    state->remote_addrlen);

    if(sbytes<0) {
      failf(data, "%s", Curl_strerror(SOCKERRNO, buffer, sizeof(buffer)));
      return CURLE_SEND_ERROR;
    }

    k->writebytecount += state->sbytes;
    Curl_pgrsSetUploadCounter(data, k->writebytecount);
    break;

  case TFTP_EVENT_TIMEOUT:

    state->retries++;
    infof(data, "Timeout waiting for block %d ACK. "
          " Retries = %d\n", NEXT_BLOCKNUM(state->block), state->retries);

    if(state->retries > state->retry_max) {
      state->error = TFTP_ERR_TIMEOUT;
      state->state = TFTP_STATE_FIN;
    }
    else {

      sbytes = sendto(state->sockfd, (void *)state->spacket.data,
                      4 + state->sbytes, SEND_4TH_ARG,
                      (struct sockaddr *)&state->remote_addr,
                      state->remote_addrlen);

      if(sbytes<0) {
        failf(data, "%s", Curl_strerror(SOCKERRNO, buffer, sizeof(buffer)));
        return CURLE_SEND_ERROR;
      }

      Curl_pgrsSetUploadCounter(data, k->writebytecount);
    }
    break;

  case TFTP_EVENT_ERROR:
    state->state = TFTP_STATE_FIN;
    setpacketevent(&state->spacket, TFTP_EVENT_ERROR);
    setpacketblock(&state->spacket, state->block);
    (void)sendto(state->sockfd, (void *)state->spacket.data, 4, SEND_4TH_ARG,
                 (struct sockaddr *)&state->remote_addr,
                 state->remote_addrlen);


    state->state = TFTP_STATE_FIN;
    break;

  default:
    failf(data, "tftp_tx: internal error, event: %i", (int)(event));
    break;
  }

  return result;
}
