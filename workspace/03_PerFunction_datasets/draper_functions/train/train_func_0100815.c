parse_der_private_key_rsa (GcrParser *self,
                           GBytes *data)
{
	gint res = GCR_ERROR_UNRECOGNIZED;
	GNode *asn = NULL;
	gulong version;
	GcrParsed *parsed;

	parsed = push_parsed (self, TRUE);

	asn = egg_asn1x_create_and_decode (pk_asn1_tab, "RSAPrivateKey", data);
	if (!asn)
		goto done;

	parsing_block (parsed, GCR_FORMAT_DER_PRIVATE_KEY_RSA, data);
	parsing_object (parsed, CKO_PRIVATE_KEY);
	parsed_ulong_attribute (parsed, CKA_KEY_TYPE, CKK_RSA);
	parsed_boolean_attribute (parsed, CKA_PRIVATE, CK_TRUE);
	res = GCR_ERROR_FAILURE;

	if (!egg_asn1x_get_integer_as_ulong (egg_asn1x_node (asn, "version", NULL), &version))
		goto done;


	if (version != 0) {
		res = GCR_ERROR_UNRECOGNIZED;
		g_message ("unsupported version of RSA key: %lu", version);
		goto done;
	}

	if (!parsed_asn1_number (parsed, asn, "modulus", CKA_MODULUS) ||
	    !parsed_asn1_number (parsed, asn, "publicExponent", CKA_PUBLIC_EXPONENT) ||
	    !parsed_asn1_number (parsed, asn, "privateExponent", CKA_PRIVATE_EXPONENT) ||
	    !parsed_asn1_number (parsed, asn, "prime1", CKA_PRIME_1) ||
	    !parsed_asn1_number (parsed, asn, "prime2", CKA_PRIME_2) ||
	    !parsed_asn1_number (parsed, asn, "coefficient", CKA_COEFFICIENT))
		goto done;

	parsed_fire (self, parsed);
	res = SUCCESS;

done:
	egg_asn1x_destroy (asn);
	if (res == GCR_ERROR_FAILURE)
		g_message ("invalid RSA key");

	pop_parsed (self, parsed);
	return res;
}
