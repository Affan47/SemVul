soap_mec_size(int alg, SOAP_MEC_KEY_TYPE *pkey)
{ if (alg & SOAP_MEC_ENV)
    return EVP_PKEY_size(pkey);
  switch (alg & SOAP_MEC_MASK & ~SOAP_MEC_ENC)
  { case SOAP_MEC_DES_CBC:
      return 20;
    case SOAP_MEC_AES128_CBC:
      return 16;
    case SOAP_MEC_AES192_CBC:
      return 24;
    case SOAP_MEC_AES256_CBC:
      return 32;
    case SOAP_MEC_AES512_CBC:
      return 64;
  }
  return 0;
}
