gnutls_protocol_get_name (gnutls_protocol_t version)
{
  const char *ret = NULL;


  GNUTLS_VERSION_ALG_LOOP (ret = p->name);
  return ret;
}
