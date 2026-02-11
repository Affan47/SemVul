undo_receive_byte(int32_t c) {
  _assert_(true);
  SocketCore* core = (SocketCore*)opq_;
  if (core->fd < 1) {
    sockseterrmsg(core, "not opened");
    return false;
  }
  if (core->rp <= core->buf) return false;
  core->rp--;
  *(unsigned char*)core->rp = c;
  return true;
}
