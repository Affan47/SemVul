store_func(hx509_context context, void *ctx, hx509_cert c)
{
    struct store_ctx *sc = ctx;
    heim_octet_string data;
    int ret;

    ret = hx509_cert_binary(context, c, &data);
    if (ret)
	return ret;

    switch (sc->format) {
    case USE_DER:
	fwrite(data.data, data.length, 1, sc->f);
	free(data.data);
	break;
    case USE_PEM:
	hx509_pem_write(context, "CERTIFICATE", NULL, sc->f,
			data.data, data.length);
	free(data.data);
	if (_hx509_cert_private_key_exportable(c)) {
	    hx509_private_key key = _hx509_cert_private_key(c);
	    ret = _hx509_private_key_export(context, key,
					    HX509_KEY_FORMAT_DER, &data);
	    if (ret)
		break;
	    hx509_pem_write(context, _hx509_private_pem_name(key), NULL, sc->f,
			    data.data, data.length);
	    free(data.data);
	}
	break;
    }

    return 0;
}
