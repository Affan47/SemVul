qos_encrypt(request_rec *r, qos_srv_config *sconf, const unsigned char *b, int l) {
  EVP_CIPHER_CTX cipher_ctx;
  int buf_len = 0;
  int len = 0;
  unsigned char *buf = apr_pcalloc(r->pool, l + EVP_CIPHER_block_size(EVP_des_ede3_cbc()));


  EVP_CIPHER_CTX_init(&cipher_ctx);
  EVP_EncryptInit(&cipher_ctx, EVP_des_ede3_cbc(), sconf->key, NULL);
  if(!EVP_EncryptUpdate(&cipher_ctx, &buf[buf_len], &len, b, l)) {
    goto failed;
  }
  buf_len+=len;
  if(!EVP_EncryptFinal(&cipher_ctx, &buf[buf_len], &len)) {
    goto failed;
  }
  buf_len+=len;
  EVP_CIPHER_CTX_cleanup(&cipher_ctx);


  {
    char *data = (char *)apr_pcalloc(r->pool, 1 + apr_base64_encode_len(buf_len));
    len = apr_base64_encode(data, (const char *)buf, buf_len);
    data[len] = '\0';
    return data;
  }

 failed:
  EVP_CIPHER_CTX_cleanup(&cipher_ctx);
  return NULL;
}
