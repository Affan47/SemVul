CtPtr ProtocolV1::wait_connect_message() {
  ldout(cct, 20) << __func__ << dendl;


  memset(&connect_msg, 0, sizeof(connect_msg));
  return READ(sizeof(connect_msg), handle_connect_message_1);
}
