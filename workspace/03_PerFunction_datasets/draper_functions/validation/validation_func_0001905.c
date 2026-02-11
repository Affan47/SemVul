ossl_x509crl_copy(VALUE self, VALUE other)
{
    X509_CRL *a, *b, *crl;

    rb_check_frozen(self);
    if (self == other) return self;
    GetX509CRL(self, a);
    SafeGetX509CRL(other, b);
    if (!(crl = X509_CRL_dup(b))) {
	ossl_raise(eX509CRLError, NULL);
    }
    X509_CRL_free(a);
    DATA_PTR(self) = crl;

    return self;
}
