tor_tls_free_all(void)
{
  if (server_tls_context) {
    tor_tls_context_t *ctx = server_tls_context;
    server_tls_context = NULL;
    tor_tls_context_decref(ctx);
  }
  if (client_tls_context) {
    tor_tls_context_t *ctx = client_tls_context;
    client_tls_context = NULL;
    tor_tls_context_decref(ctx);
  }
#ifdef V2_HANDSHAKE_CLIENT
  if (CLIENT_CIPHER_DUMMIES)
    tor_free(CLIENT_CIPHER_DUMMIES);
  if (CLIENT_CIPHER_STACK)
    sk_SSL_CIPHER_free(CLIENT_CIPHER_STACK);
#endif
}
