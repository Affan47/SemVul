nxtnet_cli_send(nxtnet_cli_t *cli,int handle,const void *buf,size_t size) {
  struct nxtnet_proto_send_cs *send_cs = (struct nxtnet_proto_send_cs*)cli->buf->data;

  cli->buf->sig = NXTNET_PROTO_SIG;
  cli->buf->cmd = NXTNET_PROTO_DIR_CS|NXTNET_PROTO_CMD_SEND;
  cli->buf->size = sizeof(struct nxtnet_proto_packet)+sizeof(struct nxtnet_proto_send_cs)+size;
  cli->buf->error = 0;
  strcpy(cli->buf->password,cli->password);

  send_cs->handle = htonl(handle);
  send_cs->size = htonl(size);
  memcpy(send_cs->data,buf,size);

  nxtnet_send(cli->sock,cli->buf);

  if (nxtnet_recv(cli->sock,cli->buf,NXTNET_PROTO_DIR_SC|NXTNET_PROTO_CMD_SEND)!=NULL) {
    struct nxtnet_proto_send_sc *send_sc = (struct nxtnet_proto_send_sc*)cli->buf->data;
    return ntohl(send_sc->size);
  }
  else return -1;
}
