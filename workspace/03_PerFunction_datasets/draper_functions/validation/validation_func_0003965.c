Send_control_msg_impl(int index, char* buf) {

  int buf_len;
  socket_info_type* socket_info;

  socket_info = &(steerer_socket_info_table.socket_info[index]);

  buf_len = strlen(buf) + 1;
  if(send_steering_msg(socket_info, buf_len, buf) == REG_FAILURE) {
    fprintf(stderr, "**DIRECT: Send_control_msg_direct: failed to send\n");
    return REG_FAILURE;
  }

  return REG_SUCCESS;
}
