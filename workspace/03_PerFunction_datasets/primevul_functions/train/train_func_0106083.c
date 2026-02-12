int amqp_send_frame_inner(amqp_connection_state_t state,
                          const amqp_frame_t *frame, int flags,
                          amqp_time_t deadline) {
  int res;
  ssize_t sent;
  amqp_bytes_t encoded;
  amqp_time_t next_timeout;


  res = amqp_frame_to_bytes(frame, state->outbound_buffer, &encoded);
  if (AMQP_STATUS_OK != res) {
    return res;
  }

start_send:

  next_timeout = amqp_time_first(deadline, state->next_recv_heartbeat);

  sent = amqp_try_send(state, encoded.bytes, encoded.len, next_timeout, flags);
  if (0 > sent) {
    return (int)sent;
  }


  if ((ssize_t)encoded.len != sent) {
    if (amqp_time_equal(next_timeout, deadline)) {

      return AMQP_STATUS_TIMEOUT;
    }

    res = amqp_try_recv(state);

    if (AMQP_STATUS_TIMEOUT == res) {
      return AMQP_STATUS_HEARTBEAT_TIMEOUT;
    } else if (AMQP_STATUS_OK != res) {
      return res;
    }

    encoded.bytes = (uint8_t *)encoded.bytes + sent;
    encoded.len -= sent;
    goto start_send;
  }

  res = amqp_time_s_from_now(&state->next_send_heartbeat,
                             amqp_heartbeat_send(state));
  return res;
}
