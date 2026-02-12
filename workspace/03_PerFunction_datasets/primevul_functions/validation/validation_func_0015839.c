CryptRsaEncrypt(
		TPM2B_PUBLIC_KEY_RSA        *cOut,
		TPM2B                       *dIn,
		OBJECT                      *key,
		TPMT_RSA_DECRYPT            *scheme,

		const TPM2B                 *label,
		RAND_STATE                  *rand

		)
{
    TPM_RC                       retVal;
    TPM2B_PUBLIC_KEY_RSA         dataIn;
    TPM2B_PUBLIC_KEY_RSA         scratch;
    size_t                       outlen;
    EVP_PKEY                    *pkey = NULL;
    EVP_PKEY_CTX                *ctx = NULL;
    const EVP_MD                *md;
    const char                  *digestname;
    unsigned char               *tmp = NULL;


    if(dIn == &cOut->b)
	{
	    MemoryCopy2B(&dataIn.b, dIn, sizeof(dataIn.t.buffer));
	    dIn = &dataIn.b;
	}

    pAssert(sizeof(cOut->t.buffer) >= key->publicArea.unique.rsa.t.size);
    cOut->t.size = key->publicArea.unique.rsa.t.size;
    TEST(scheme->scheme);

    retVal = InitOpenSSLRSAPublicKey(key, &pkey);
    if (retVal != TPM_RC_SUCCESS)
        return retVal;

    ctx = EVP_PKEY_CTX_new(pkey, NULL);
    if (ctx == NULL ||
        EVP_PKEY_encrypt_init(ctx) <= 0)
        ERROR_RETURN(TPM_RC_FAILURE);

    switch(scheme->scheme)
	{
          case ALG_NULL_VALUE:
	    {
		INT32                 i;
		INT32                 dSize = dIn->size;


		for(i = 0; (i < dSize) && (dIn->buffer[i] == 0); i++);
		dSize -= i;
		scratch.t.size = cOut->t.size;
		pAssert(scratch.t.size <= sizeof(scratch.t.buffer));
		if(dSize > scratch.t.size)
		    ERROR_RETURN(TPM_RC_VALUE);

		memset(scratch.t.buffer, 0, scratch.t.size - dSize);

		memcpy(&scratch.t.buffer[scratch.t.size - dSize], &dIn->buffer[i], dSize);

		dIn = &scratch.b;
	    }
            if (EVP_PKEY_CTX_set_rsa_padding(ctx, RSA_NO_PADDING) <= 0)
                ERROR_RETURN(TPM_RC_FAILURE);
            break;
          case ALG_RSAES_VALUE:
            if (EVP_PKEY_CTX_set_rsa_padding(ctx, RSA_PKCS1_PADDING) <= 0)
                ERROR_RETURN(TPM_RC_FAILURE);
            break;
          case ALG_OAEP_VALUE:
            digestname = GetDigestNameByHashAlg(scheme->details.oaep.hashAlg);
            if (digestname == NULL)
                ERROR_RETURN(TPM_RC_VALUE);

            md = EVP_get_digestbyname(digestname);
            if (md == NULL ||
                EVP_PKEY_CTX_set_rsa_padding(ctx, RSA_PKCS1_OAEP_PADDING) <= 0 ||
                EVP_PKEY_CTX_set_rsa_oaep_md(ctx, md) <= 0)
                ERROR_RETURN(TPM_RC_FAILURE);

            if (label->size > 0) {
                tmp = malloc(label->size);
                if (tmp == NULL)
                    ERROR_RETURN(TPM_RC_FAILURE);
                memcpy(tmp, label->buffer, label->size);
            }

            if (EVP_PKEY_CTX_set0_rsa_oaep_label(ctx, tmp, label->size) <= 0)
                ERROR_RETURN(TPM_RC_FAILURE);
            tmp = NULL;
            break;
          default:
            ERROR_RETURN(TPM_RC_SCHEME);
            break;
	}

    outlen = cOut->t.size;

    if (EVP_PKEY_encrypt(ctx, cOut->t.buffer, &outlen,
                         dIn->buffer, dIn->size) <= 0)
        ERROR_RETURN(TPM_RC_FAILURE);

    cOut->t.size = outlen;

 Exit:
    EVP_PKEY_free(pkey);
    EVP_PKEY_CTX_free(ctx);
    free(tmp);

    return retVal;
}
