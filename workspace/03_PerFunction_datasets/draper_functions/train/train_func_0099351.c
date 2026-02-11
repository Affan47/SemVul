i2d_PUBKEY(EVP_PKEY *a, unsigned char **pp)
	{
	X509_PUBKEY *xpk=NULL;
	int ret;
	if(!a) return 0;
	if(!X509_PUBKEY_set(&xpk, a)) return 0;
	ret = i2d_X509_PUBKEY(xpk, pp);
	X509_PUBKEY_free(xpk);
	return ret;
	}
