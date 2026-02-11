pseudo_tcp_socket_notify_mtu(PseudoTcpSocket *self, guint16 mtu)
{
  PseudoTcpSocketPrivate *priv = self->priv;
  priv->mtu_advise = mtu;
  if (priv->state == TCP_ESTABLISHED) {
    adjustMTU(self);
  }
}
