rest_proxy_call_lookup_response_header (RestProxyCall *call,
                                        const gchar   *header)
{
  RestProxyCallPrivate *priv;

  g_return_val_if_fail (REST_IS_PROXY_CALL (call), NULL);

  priv = GET_PRIVATE (call);

  if (!priv->response_headers)
  {
    return NULL;
  }

  return g_hash_table_lookup (priv->response_headers, header);
}
