PHP_FUNCTION(openssl_csr_get_public_key)
{
	zval * zcsr;
	zend_bool use_shortnames = 1;
	zend_resource *csr_resource;

	X509_REQ *orig_csr, *csr;
	EVP_PKEY *tpubkey;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "z|b", &zcsr, &use_shortnames) == FAILURE) {
		return;
	}

	orig_csr = php_openssl_csr_from_zval(zcsr, 0, &csr_resource);

	if (orig_csr == NULL) {
		RETURN_FALSE;
	}

#if PHP_OPENSSL_API_VERSION >= 0x10100


	csr = X509_REQ_dup(orig_csr);
#else
	csr = orig_csr;
#endif


	tpubkey = X509_REQ_get_pubkey(csr);

	if (csr != orig_csr) {

		X509_REQ_free(csr);
	}

	if (!csr_resource) {

		X509_REQ_free(orig_csr);
	}

	if (tpubkey == NULL) {
		php_openssl_store_errors();
		RETURN_FALSE;
	}

	RETURN_RES(zend_register_resource(tpubkey, le_key));
}
