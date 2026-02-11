cleanup_listener_connection_samples(const int index) {
  if(socket_info_table.socket_info[index].listener_status == REG_COMMS_STATUS_LISTENING) {
    close_listener_handle_samples(index);
  }

  if(socket_info_table.socket_info[index].comms_status == REG_COMMS_STATUS_CONNECTED) {
    close_connector_handle_samples(index);
  }


  sprintf(socket_info_table.socket_info[index].listener_hostname, "NOT_SET");
  socket_info_table.socket_info[index].listener_port = 0;
}
