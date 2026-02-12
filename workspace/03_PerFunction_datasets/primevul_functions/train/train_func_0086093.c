ca_subjectpubkey_digest(X509 *x509, uint8_t *md, unsigned int *size)
{
	EVP_PKEY	*pkey;
	uint8_t		*buf = NULL;
	int		 buflen;

	if (*size < SHA_DIGEST_LENGTH)
		return (-1);


	if ((pkey = X509_get_pubkey(x509)) == NULL)
		return (-1);
	buflen = i2d_PUBKEY(pkey, &buf);
	EVP_PKEY_free(pkey);
	if (buflen == 0)
		return (-1);
	if (!EVP_Digest(buf, buflen, md, size, EVP_sha1(), NULL)) {
		free(buf);
		return (-1);
	}
	free(buf);

	return (0);
}
