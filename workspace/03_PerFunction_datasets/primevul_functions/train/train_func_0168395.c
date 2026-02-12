aes_ctr_encrypt(struct ssh_cipher_struct *cipher,
                void *in,
                void *out,
                size_t len)
{
  unsigned char tmp_buffer[AES_BLOCK_SIZE];
  unsigned int num=0;


#ifdef HAVE_OPENSSL_CRYPTO_CTR128_ENCRYPT
  CRYPTO_ctr128_encrypt(in, out, len, &cipher->aes_key->key, cipher->aes_key->IV, tmp_buffer, &num, (block128_f)AES_encrypt);
#else
  AES_ctr128_encrypt(in, out, len, &cipher->aes_key->key, cipher->aes_key->IV, tmp_buffer, &num);
#endif
}
