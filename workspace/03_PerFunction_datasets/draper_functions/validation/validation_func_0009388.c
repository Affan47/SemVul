sxnet_i2r(X509V3_EXT_METHOD *method, SXNET *sx, BIO *out,
	     int indent)
{
	long v;
	char *tmp;
	SXNETID *id;
	int i;
	v = ASN1_INTEGER_get(sx->version);
	BIO_printf(out, "%*sVersion: %ld (0x%lX)", indent, "", v + 1, v);
	for(i = 0; i < sk_SXNETID_num(sx->ids); i++) {
		id = sk_SXNETID_value(sx->ids, i);
		tmp = i2s_ASN1_INTEGER(NULL, id->zone);
		BIO_printf(out, "\n%*sZone: %s, User: ", indent, "", tmp);
		OPENSSL_free(tmp);
		M_ASN1_OCTET_STRING_print(out, id->user);
	}
	return 1;
}
