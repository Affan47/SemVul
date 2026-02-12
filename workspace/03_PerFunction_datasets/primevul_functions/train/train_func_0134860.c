_gnutls_compression_get_id (int num)
{
  gnutls_compression_method_t ret = -1;


  GNUTLS_COMPRESSION_ALG_LOOP_NUM (ret = p->id);

  return ret;
}
