gcry_cipher_encrypt (gcry_cipher_hd_t h,
                     void *out, size_t outsize,
                     const void *in, size_t inlen)
{
  if (!fips_is_operational ())
    {

      if (out)
        memset (out, 0x42, outsize);
      return gpg_error (fips_not_operational ());
    }

  return _gcry_cipher_encrypt (h, out, outsize, in, inlen);
}
