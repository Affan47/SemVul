static long tftp_state_timeout(struct connectdata *conn, tftp_event_t *event)
{
  time_t                current;
  tftp_state_data_t     *state = (tftp_state_data_t *)conn->proto.tftpc;

  if(event)
    *event = TFTP_EVENT_NONE;

  time(&current);
  if(current > state->max_time) {
    DEBUGF(infof(conn->data, "timeout: %ld > %ld\n",
                 (long)current, (long)state->max_time));
    state->error = TFTP_ERR_TIMEOUT;
    state->state = TFTP_STATE_FIN;
    return 0;
  }
  if(current > state->rx_time + state->retry_time) {
    if(event)
      *event = TFTP_EVENT_TIMEOUT;
    time(&state->rx_time);
  }


  return (long)(state->max_time - current);
}
