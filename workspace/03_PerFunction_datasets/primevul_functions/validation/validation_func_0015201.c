BOOL license_send_client_info(rdpLicense* license, const LICENSE_BLOB* calBlob, BYTE* signature)
{
	wStream* s;


	UINT32 PlatformId = PLATFORMID;
	UINT32 PreferredKeyExchangeAlg = KEY_EXCHANGE_ALG_RSA;

	s = license_send_stream_init(license);
	if (!s)
		return FALSE;

	Stream_Write_UINT32(s, PreferredKeyExchangeAlg);
	Stream_Write_UINT32(s, PlatformId);


	Stream_Write(s, license->ClientRandom, CLIENT_RANDOM_LENGTH);


	if (!license_write_encrypted_premaster_secret_blob(s, license->EncryptedPremasterSecret,
	                                                   license->ModulusLength))
		goto error;


	if (!license_write_binary_blob(s, calBlob))
		goto error;


	if (!license_write_binary_blob(s, license->EncryptedHardwareId))
		goto error;


	Stream_Write(s, signature, LICENSING_ENCRYPTION_KEY_LENGTH);

	return license_send(license, s, LICENSE_INFO);

error:
	Stream_Release(s);
	return FALSE;
}
