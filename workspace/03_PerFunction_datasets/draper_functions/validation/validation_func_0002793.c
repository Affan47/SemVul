certs_s2i(struct v3_ext_method*, struct v3_ext_ctx*, char *data)
{
  STACK_OF(X509) *certs =
    (STACK_OF(X509) *)data;
  int i = 0;

  if (data) {
    AC_CERTS *a = AC_CERTS_new();

    sk_X509_pop_free(a->stackcert, X509_free);
    a->stackcert = sk_X509_new_null();


    for (i =0; i < sk_X509_num(certs); i++)
      sk_X509_push(a->stackcert, X509_dup(sk_X509_value(certs, i)));

    return a;
  }

  return NULL;
}
