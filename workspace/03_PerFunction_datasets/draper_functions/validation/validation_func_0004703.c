next_serial(const char *serialfile)
	{
	int ret = 0;
	BIO *in = NULL;
	ASN1_INTEGER *serial = NULL;
	BIGNUM *bn = NULL;

	if (!(serial = ASN1_INTEGER_new())) goto err;

	if (!(in = BIO_new_file(serialfile, "r")))
		{
		ERR_clear_error();
		BIO_printf(bio_err, "Warning: could not open file %s for "
			   "reading, using serial number: 1\n", serialfile);
		if (!ASN1_INTEGER_set(serial, 1)) goto err;
		}
	else
		{
		char buf[1024];
		if (!a2i_ASN1_INTEGER(in, serial, buf, sizeof(buf)))
			{
			BIO_printf(bio_err, "unable to load number from %s\n",
				   serialfile);
			goto err;
			}
		if (!(bn = ASN1_INTEGER_to_BN(serial, NULL))) goto err;
		ASN1_INTEGER_free(serial);
		serial = NULL;
		if (!BN_add_word(bn, 1)) goto err;
		if (!(serial = BN_to_ASN1_INTEGER(bn, NULL))) goto err;
		}
	ret = 1;
 err:
	if (!ret)
		{
		ASN1_INTEGER_free(serial);
		serial = NULL;
		}
	BIO_free_all(in);
	BN_free(bn);
	return serial;
	}
