gnutls_mac_get_name (gnutls_mac_algorithm_t algorithm)
{
  const char *ret = NULL;


  GNUTLS_HASH_ALG_LOOP (ret = p->name);

  return ret;
}
