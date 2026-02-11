ossl_rsa_to_text(VALUE self)
{
    EVP_PKEY *pkey;
    BIO *out;
    VALUE str;

    GetPKeyRSA(self, pkey);
    if (!(out = BIO_new(BIO_s_mem()))) {
	ossl_raise(eRSAError, NULL);
    }
    if (!RSA_print(out, pkey->pkey.rsa, 0)) {
	BIO_free(out);
	ossl_raise(eRSAError, NULL);
    }
    str = ossl_membio2str(out);

    return str;
}
