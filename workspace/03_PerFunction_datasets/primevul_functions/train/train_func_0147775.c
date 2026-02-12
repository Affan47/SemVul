static bool encrypt_des(const unsigned char *in, unsigned char *out,
                        const unsigned char *key_56)
{
  char key[8];
  _CIPHER_Control_T ctl;


  ctl.Func_ID = ENCRYPT_ONLY;
  ctl.Data_Len = sizeof(key);


  extend_key_56_to_64(key_56, ctl.Crypto_Key);


  Curl_des_set_odd_parity((unsigned char *) ctl.Crypto_Key, ctl.Data_Len);


  _CIPHER((_SPCPTR *) &out, &ctl, (_SPCPTR *) &in);

  return TRUE;
}
