static CURLcode tftp_connect(struct connectdata *conn, bool *done)
{
  tftp_state_data_t *state;
  int blksize;
  int need_blksize;

  blksize = TFTP_BLKSIZE_DEFAULT;

  state = conn->proto.tftpc = calloc(1, sizeof(tftp_state_data_t));
  if(!state)
    return CURLE_OUT_OF_MEMORY;


  if(conn->data->set.tftp_blksize) {
    blksize = (int)conn->data->set.tftp_blksize;
    if(blksize > TFTP_BLKSIZE_MAX || blksize < TFTP_BLKSIZE_MIN)
      return CURLE_TFTP_ILLEGAL;
  }

  need_blksize = blksize;

  if(need_blksize < TFTP_BLKSIZE_DEFAULT)
    need_blksize = TFTP_BLKSIZE_DEFAULT;

  if(!state->rpacket.data) {
    state->rpacket.data = calloc(1, need_blksize + 2 + 2);

    if(!state->rpacket.data)
      return CURLE_OUT_OF_MEMORY;
  }

  if(!state->spacket.data) {
    state->spacket.data = calloc(1, need_blksize + 2 + 2);

    if(!state->spacket.data)
      return CURLE_OUT_OF_MEMORY;
  }


  connclose(conn, "TFTP");

  state->conn = conn;
  state->sockfd = state->conn->sock[FIRSTSOCKET];
  state->state = TFTP_STATE_START;
  state->error = TFTP_ERR_NONE;
  state->blksize = TFTP_BLKSIZE_DEFAULT;
  state->requested_blksize = blksize;

  ((struct sockaddr *)&state->local_addr)->sa_family =
    (CURL_SA_FAMILY_T)(conn->ip_addr->ai_family);

  tftp_set_timeouts(state);

  if(!conn->bits.bound) {


    int rc = bind(state->sockfd, (struct sockaddr *)&state->local_addr,
                  conn->ip_addr->ai_addrlen);
    if(rc) {
      char buffer[STRERROR_LEN];
      failf(conn->data, "bind() failed; %s",
            Curl_strerror(SOCKERRNO, buffer, sizeof(buffer)));
      return CURLE_COULDNT_CONNECT;
    }
    conn->bits.bound = TRUE;
  }

  Curl_pgrsStartNow(conn->data);

  *done = TRUE;

  return CURLE_OK;
}
