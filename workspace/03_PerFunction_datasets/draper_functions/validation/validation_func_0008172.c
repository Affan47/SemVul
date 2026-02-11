trust_prompt_get_issuers (CERTCertDBHandle *certdb,
                          const ENamedParameters *parameters)
{
	GSList *issuers = NULL;
	CERTCertificate *cert;
	SECItem derCert;
	gsize derCert_len = 0;
	gint ii;

	g_return_val_if_fail (certdb != NULL, NULL);
	g_return_val_if_fail (parameters != NULL, NULL);

	for (ii = 0; ii >= 0; ii++) {
		const gchar *base64_cert;

		if (ii == 0) {
			base64_cert = e_named_parameters_get (parameters, "issuer");
		} else {
			gchar *key;

			key = g_strdup_printf ("issuer-%d", ii);
			base64_cert = e_named_parameters_get (parameters, key);
			g_free (key);
		}

		if (!base64_cert)
			break;

		derCert.type = siDERCertBuffer;
		derCert.data = g_base64_decode (base64_cert, &derCert_len);
		if (!derCert.data)
			break;

		derCert.len = derCert_len;

		cert = CERT_NewTempCertificate (certdb, &derCert, NULL, PR_FALSE, PR_TRUE);
		g_free (derCert.data);

		if (!cert)
			break;

		issuers = g_slist_prepend (issuers, cert);
	}

	return g_slist_reverse (issuers);
}
