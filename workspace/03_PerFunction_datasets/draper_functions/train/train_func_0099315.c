yield_op (GTlsConnectionGnutls   *gnutls,
	  GTlsConnectionGnutlsOp  op)
{
  g_mutex_lock (&gnutls->priv->op_mutex);

  if (op == G_TLS_CONNECTION_GNUTLS_OP_HANDSHAKE)
    gnutls->priv->handshaking = FALSE;
  if (op == G_TLS_CONNECTION_GNUTLS_OP_CLOSE)
    gnutls->priv->closing = FALSE;

  if (op != G_TLS_CONNECTION_GNUTLS_OP_WRITE)
    gnutls->priv->reading = FALSE;
  if (op != G_TLS_CONNECTION_GNUTLS_OP_READ)
    gnutls->priv->writing = FALSE;

  g_cancellable_cancel (gnutls->priv->waiting_for_op);
  g_mutex_unlock (&gnutls->priv->op_mutex);
}
