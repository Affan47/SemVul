static CURLcode tftp_set_timeouts(tftp_state_data_t *state)
{
  time_t maxtime, timeout;
  timediff_t timeout_ms;
  bool start = (state->state == TFTP_STATE_START) ? TRUE : FALSE;

  time(&state->start_time);


  timeout_ms = Curl_timeleft(state->conn->data, NULL, start);

  if(timeout_ms < 0) {

    failf(state->conn->data, "Connection time-out");
    return CURLE_OPERATION_TIMEDOUT;
  }

  if(start) {

    maxtime = (time_t)(timeout_ms + 500) / 1000;
    state->max_time = state->start_time + maxtime;


    timeout = maxtime;


    state->retry_max = (int)timeout/5;

    if(state->retry_max < 1)

      state->retry_max = 1;


    state->retry_time = (int)timeout/state->retry_max;
    if(state->retry_time<1)
      state->retry_time = 1;

  }
  else {
    if(timeout_ms > 0)
      maxtime = (time_t)(timeout_ms + 500) / 1000;
    else
      maxtime = 3600;

    state->max_time = state->start_time + maxtime;


    timeout = maxtime;


    state->retry_max = (int)timeout/5;
  }

  if(state->retry_max<3)
    state->retry_max = 3;

  if(state->retry_max>50)
    state->retry_max = 50;


  state->retry_time = (int)(timeout/state->retry_max);
  if(state->retry_time<1)
    state->retry_time = 1;

  infof(state->conn->data,
        "set timeouts for state %d; Total %ld, retry %d maxtry %d\n",
        (int)state->state, (long)(state->max_time-state->start_time),
        state->retry_time, state->retry_max);


  time(&state->rx_time);

  return CURLE_OK;
}
