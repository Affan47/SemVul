ssh_channel_poll(ssh_channel channel, int is_stderr){
  ssh_buffer stdbuf;

  if(channel == NULL) {
      return SSH_ERROR;
  }

  stdbuf = channel->stdout_buffer;

  if (is_stderr) {
    stdbuf = channel->stderr_buffer;
  }

  if (buffer_get_rest_len(stdbuf) == 0 && channel->remote_eof == 0) {
    if (channel->session->session_state == SSH_SESSION_STATE_ERROR){
      return SSH_ERROR;
    }
    if (ssh_handle_packets(channel->session, SSH_TIMEOUT_NONBLOCKING)==SSH_ERROR) {
      return SSH_ERROR;
    }
  }

  if (buffer_get_rest_len(stdbuf) > 0){
  	return buffer_get_rest_len(stdbuf);
  }

  if (channel->remote_eof) {
    return SSH_EOF;
  }

  return buffer_get_rest_len(stdbuf);
}
