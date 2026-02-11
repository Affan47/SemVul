X509_NAME_hash(X509_NAME *x)
	{
	unsigned long ret=0;
	unsigned char md[SHA_DIGEST_LENGTH];


	i2d_X509_NAME(x,NULL);
	if (!EVP_Digest(x->canon_enc, x->canon_enclen, md, NULL, EVP_sha1(),
		NULL))
		return 0;

	ret=(	((unsigned long)md[0]     )|((unsigned long)md[1]<<8L)|
		((unsigned long)md[2]<<16L)|((unsigned long)md[3]<<24L)
		)&0xffffffffL;
	return(ret);
	}
