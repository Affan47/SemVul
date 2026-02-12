CtPtr ProtocolV1::wait_message() {
  if (state != OPENED) {
    return nullptr;
  }

  ldout(cct, 20) << __func__ << dendl;

  return READ(sizeof(char), handle_message);
}
