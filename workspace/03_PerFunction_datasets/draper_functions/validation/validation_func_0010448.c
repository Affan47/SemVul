evp_des_encrypt_null_ivec(krb5_context context,
			  struct _krb5_key_data *key,
			  void *data,
			  size_t len,
			  krb5_boolean encryptp,
			  int usage,
			  void *ignore_ivec)
{
    struct _krb5_evp_schedule *ctx = key->schedule->data;
    EVP_CIPHER_CTX *c;
    DES_cblock ivec;
    memset(&ivec, 0, sizeof(ivec));
    c = encryptp ? &ctx->ectx : &ctx->dctx;
    EVP_CipherInit_ex(c, NULL, NULL, NULL, (void *)&ivec, -1);
    EVP_Cipher(c, data, data, len);
    return 0;
}
