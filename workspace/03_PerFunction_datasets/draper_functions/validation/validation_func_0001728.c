EVP_PKEY_meth_new(int id, int flags)
	{
	EVP_PKEY_METHOD *pmeth;
	pmeth = OPENSSL_malloc(sizeof(EVP_PKEY_METHOD));
	if (!pmeth)
		return NULL;

	memset(pmeth, 0, sizeof(EVP_PKEY_METHOD));

	pmeth->pkey_id = id;
	pmeth->flags = flags | EVP_PKEY_FLAG_DYNAMIC;

	pmeth->init = 0;
	pmeth->copy = 0;
	pmeth->cleanup = 0;
	pmeth->paramgen_init = 0;
	pmeth->paramgen = 0;
	pmeth->keygen_init = 0;
	pmeth->keygen = 0;
	pmeth->sign_init = 0;
	pmeth->sign = 0;
	pmeth->verify_init = 0;
	pmeth->verify = 0;
	pmeth->verify_recover_init = 0;
	pmeth->verify_recover = 0;
	pmeth->signctx_init = 0;
	pmeth->signctx = 0;
	pmeth->verifyctx_init = 0;
	pmeth->verifyctx = 0;
	pmeth->encrypt_init = 0;
	pmeth->encrypt = 0;
	pmeth->decrypt_init = 0;
	pmeth->decrypt = 0;
	pmeth->derive_init = 0;
	pmeth->derive = 0;
	pmeth->ctrl = 0;
	pmeth->ctrl_str = 0;

	return pmeth;
	}
