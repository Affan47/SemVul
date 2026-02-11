credssp_encode_ts_credentials(rdpCredssp* credssp)
{
	asn_enc_rval_t enc_rval;
	TSCredentials_t *ts_credentials;
	TSPasswordCreds_t *ts_passwoFRDP_creds;
	BLOB ts_passwoFRDP_creds_buffer = { 0 };

	ts_credentials = calloc(1, sizeof(TSCredentials_t));
	ts_credentials->credType = 1;

	ts_passwoFRDP_creds = calloc(1, sizeof(TSPasswordCreds_t));


	ts_passwoFRDP_creds->domainName.buf = credssp->ntlmssp->domain.data;
	ts_passwoFRDP_creds->domainName.size = credssp->ntlmssp->domain.length;


	ts_passwoFRDP_creds->userName.buf = credssp->ntlmssp->username.data;
	ts_passwoFRDP_creds->userName.size = credssp->ntlmssp->username.length;


	ts_passwoFRDP_creds->password.buf = credssp->ntlmssp->password.data;
	ts_passwoFRDP_creds->password.size = credssp->ntlmssp->password.length;


	enc_rval = der_encode(&asn_DEF_TSPasswordCreds, ts_passwoFRDP_creds, asn1_write, 0);

	if (enc_rval.encoded != -1)
	{
		freerdp_blob_alloc(&ts_passwoFRDP_creds_buffer, enc_rval.encoded);

		enc_rval = der_encode_to_buffer(&asn_DEF_TSPasswordCreds, ts_passwoFRDP_creds,
			ts_passwoFRDP_creds_buffer.data, ts_passwoFRDP_creds_buffer.length);
	}

	ts_credentials->credentials.buf = ts_passwoFRDP_creds_buffer.data;
	ts_credentials->credentials.size = ts_passwoFRDP_creds_buffer.length;


	enc_rval = der_encode(&asn_DEF_TSCredentials, ts_credentials, asn1_write, 0);

	if (enc_rval.encoded != -1)
	{
		freerdp_blob_alloc(&credssp->ts_credentials, enc_rval.encoded);

		enc_rval = der_encode_to_buffer(&asn_DEF_TSCredentials, ts_credentials,
			credssp->ts_credentials.data, credssp->ts_credentials.length);
	}

	freerdp_blob_free(&ts_passwoFRDP_creds_buffer);
	free(ts_credentials);
	free(ts_passwoFRDP_creds);
}
