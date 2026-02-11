CMS_SignerInfo_set1_signer_cert(CMS_SignerInfo *si, X509 *signer)
	{
	if (signer)
		{
		CRYPTO_add(&signer->references, 1, CRYPTO_LOCK_X509);
		if (si->pkey)
			EVP_PKEY_free(si->pkey);
		si->pkey = X509_get_pubkey(signer);
		}
	if (si->signer)
		X509_free(si->signer);
	si->signer = signer;
	}
