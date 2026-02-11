_gnutls_cal_PRF_A (gnutls_mac_algorithm_t algorithm,
                   const void *secret, int secret_size,
                   const void *seed, int seed_size, void *result)
{
  digest_hd_st td1;
  int ret;

  ret = _gnutls_hmac_init (&td1, algorithm, secret, secret_size);
  if (ret < 0)
    {
      gnutls_assert ();
      return ret;
    }

  _gnutls_hmac (&td1, seed, seed_size);
  _gnutls_hmac_deinit (&td1, result);

  return 0;
}
