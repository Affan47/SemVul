EVP_PKEY_save_parameters(EVP_PKEY *pkey, int mode)
	{
#ifndef OPENSSL_NO_DSA
	if (pkey->type == EVP_PKEY_DSA)
		{
		int ret=pkey->save_parameters;

		if (mode >= 0)
			pkey->save_parameters=mode;
		return(ret);
		}
#endif
#ifndef OPENSSL_NO_EC
	if (pkey->type == EVP_PKEY_EC)
		{
		int ret = pkey->save_parameters;

		if (mode >= 0)
			pkey->save_parameters = mode;
		return(ret);
		}
#endif
	return(0);
	}
