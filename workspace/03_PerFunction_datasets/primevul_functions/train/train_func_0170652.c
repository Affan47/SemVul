int X509_add_certs(STACK_OF(X509) *sk, STACK_OF(X509) *certs, int flags)

{
    int n = sk_X509_num(certs);
    int i;

    for (i = 0; i < n; i++) {
        int j = (flags & X509_ADD_FLAG_PREPEND) == 0 ? i : n - 1 - i;


        if (!X509_add_cert(sk, sk_X509_value(certs, j), flags))
            return 0;
    }
    return 1;
}
