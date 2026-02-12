size_t mg_ws_wrap(struct mg_connection *c, size_t len, int op) {
  uint8_t header[14], *p;
  size_t header_len = mkhdr(len, op, c->is_client, header);


  mg_iobuf_add(&c->send, c->send.len, NULL, header_len, MG_IO_SIZE);
  p = &c->send.buf[c->send.len - len];
  memmove(p, p - header_len, len);
  memcpy(p - header_len, header, header_len);
  mg_ws_mask(c, len);

  return c->send.len;
}
