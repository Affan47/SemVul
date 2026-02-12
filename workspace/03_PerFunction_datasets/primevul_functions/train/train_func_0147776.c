static bool encrypt_des(const unsigned char *in, unsigned char *out,
                        const unsigned char *key_56)
{
  char key[8];
  size_t out_len;
  CCCryptorStatus err;


  extend_key_56_to_64(key_56, key);


  Curl_des_set_odd_parity((unsigned char *) key, sizeof(key));


  err = CCCrypt(kCCEncrypt, kCCAlgorithmDES, kCCOptionECBMode, key,
                kCCKeySizeDES, NULL, in, 8 , out,
                8 , &out_len);

  return err == kCCSuccess;
}
