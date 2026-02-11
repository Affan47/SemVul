cert_errors_to_reason (GTlsCertificateFlags flags)
{
	struct _convert_table {
		GTlsCertificateFlags flag;
		const gchar *description;
	} convert_table[] = {
		{ G_TLS_CERTIFICATE_UNKNOWN_CA,
		  N_("The signing certificate authority is not known.") },
		{ G_TLS_CERTIFICATE_BAD_IDENTITY,
		  N_("The certificate does not match the expected identity of the site that it was retrieved from.") },
		{ G_TLS_CERTIFICATE_NOT_ACTIVATED,
		  N_("The certificate's activation time is still in the future.") },
		{ G_TLS_CERTIFICATE_EXPIRED,
		  N_("The certificate has expired.") },
		{ G_TLS_CERTIFICATE_REVOKED,
		  N_("The certificate has been revoked according to the connection's certificate revocation list.") },
		{ G_TLS_CERTIFICATE_INSECURE,
		  N_("The certificate's algorithm is considered insecure.") }
	};

	GString *reason = g_string_new ("");
	gint ii;

	for (ii = 0; ii < G_N_ELEMENTS (convert_table); ii++) {
		if ((flags & convert_table[ii].flag) != 0) {
			if (reason->len > 0)
				g_string_append (reason, "\n");

			g_string_append (reason, _(convert_table[ii].description));
		}
	}

	return g_string_free (reason, FALSE);
}
