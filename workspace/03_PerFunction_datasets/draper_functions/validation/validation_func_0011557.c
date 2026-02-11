_dccnet_accept(struct dccproxy *p, int sock) {
  int newsock;
  int len;


  len = sizeof(struct sockaddr_in);
  newsock = accept(sock, (struct sockaddr *)&(p->sendee_addr), &len);
  if (newsock == -1) {
    syscall_fail("accept", 0, 0);
    p->dead = 1;
    return;
  }


  net_close(&(p->sendee_sock));
  p->sendee_status &= ~(DCC_SENDEE_LISTENING);
  p->sendee_sock = newsock;
  net_create(&(p->sendee_sock));

  if (p->sendee_sock != -1) {
    p->sendee_status |= DCC_SENDEE_CONNECTED;

    if (p->type & DCC_SEND) {
      dccsend_accepted(p);
    } else if (p->type & DCC_CHAT) {
      dccchat_accepted(p);
    }

    debug("DCC Sendee connected from %s:%d",
          inet_ntoa(p->sendee_addr.sin_addr),
          ntohs(p->sendee_addr.sin_port));
  }
}
