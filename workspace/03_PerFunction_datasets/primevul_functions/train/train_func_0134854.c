gnutls_cipher_get_name (gnutls_cipher_algorithm_t algorithm)
{
  const char *ret = NULL;


  GNUTLS_ALG_LOOP (ret = p->name);

  return ret;
}
