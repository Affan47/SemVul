gkm_dh_mechanism_derive (GkmSession *session, CK_MECHANISM_PTR mech, GkmObject *base,
                         CK_ATTRIBUTE_PTR attrs, CK_ULONG n_attrs, GkmObject **derived)
{
	gcry_mpi_t peer = NULL;
	gcry_mpi_t prime;
	gcry_mpi_t priv;
	gcry_error_t gcry;
	CK_ATTRIBUTE attr;
	GArray *array;
	gsize n_actual = 0;
	CK_ULONG n_value = 0;
	guchar *value;
	GkmTransaction *transaction;
	CK_KEY_TYPE type;

	g_return_val_if_fail (GKM_IS_DH_PRIVATE_KEY (base), CKR_GENERAL_ERROR);

	if (mech->ulParameterLen && mech->pParameter) {
		gcry = gcry_mpi_scan (&peer, GCRYMPI_FMT_USG, mech->pParameter,
		                      mech->ulParameterLen, NULL);
		if (gcry != 0)
			peer = NULL;
	}

	if (peer == NULL)
		return CKR_MECHANISM_PARAM_INVALID;

	prime = gkm_dh_key_get_prime (GKM_DH_KEY (base));
	priv = gkm_dh_private_key_get_value (GKM_DH_PRIVATE_KEY (base));


	if (!gkm_attributes_find_ulong (attrs, n_attrs, CKA_VALUE_LEN, &n_value)) {
		if (gkm_attributes_find_ulong (attrs, n_attrs, CKA_KEY_TYPE, &type))
			n_value = gkm_crypto_secret_key_length (type);
	}


	if (n_value == 0)
		n_value = (gcry_mpi_get_nbits (prime) + 7) / 8;

	value = egg_dh_gen_secret (peer, priv, prime, &n_actual);
	gcry_mpi_release (peer);

	if (value == NULL)
		return CKR_FUNCTION_FAILED;


	array = g_array_new (FALSE, FALSE, sizeof (CK_ATTRIBUTE));


	attr.type = CKA_VALUE;
	attr.ulValueLen = n_value;


	if (n_actual > n_value) {
		attr.pValue = value + (n_actual - n_value);


	} else if (n_actual < n_value) {
		value = egg_secure_realloc (value, n_value);
		memmove (value + (n_value - n_actual), value, n_actual);
		memset (value, 0, (n_value - n_actual));
		attr.pValue = value;


	} else {
		attr.pValue = value;
	}

	g_array_append_val (array, attr);


	g_array_append_vals (array, attrs, n_attrs);

	transaction = gkm_transaction_new ();


	*derived = gkm_session_create_object_for_attributes (session, transaction,
	                                                     (CK_ATTRIBUTE_PTR)array->data, array->len);

	egg_secure_free (value);
	g_array_free (array, TRUE);

	return gkm_transaction_complete_and_unref (transaction);
}
