hx509_get_one_cert(hx509_context context, hx509_certs certs, hx509_cert *c)
{
    hx509_cursor cursor;
    int ret;

    *c = NULL;

    ret = hx509_certs_start_seq(context, certs, &cursor);
    if (ret)
	return ret;

    ret = hx509_certs_next_cert(context, certs, cursor, c);
    if (ret)
	return ret;

    hx509_certs_end_seq(context, certs, cursor);
    return 0;
}
