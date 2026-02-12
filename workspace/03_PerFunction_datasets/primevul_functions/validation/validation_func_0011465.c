void ProtocolV1::connect() {
  this->state = START_CONNECT;


  authorizer_buf.clear();

  memset(&connect_msg, 0, sizeof(connect_msg));
  memset(&connect_reply, 0, sizeof(connect_reply));

  global_seq = messenger->get_global_seq();
}
