get_x509_subject_email(X509 *x)
{
    char *result = NULL;
    STACK_OF(OPENSSL_STRING) *emails = X509_get1_email(x);
    if (sk_OPENSSL_STRING_num(emails) > 0) {

	result = cpystr(sk_OPENSSL_STRING_value(emails, 0));
    }
    X509_email_free(emails);
    return result;
}
