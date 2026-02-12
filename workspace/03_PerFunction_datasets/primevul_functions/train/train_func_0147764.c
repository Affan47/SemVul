static void setup_des_key(const unsigned char *key_56,
                          gcry_cipher_hd_t *des)
{
  char key[8];


  extend_key_56_to_64(key_56, key);


  Curl_des_set_odd_parity((unsigned char *) key, sizeof(key));


  gcry_cipher_setkey(*des, key, sizeof(key));
}
