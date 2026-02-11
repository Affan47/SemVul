Trspi_UnloadBlob_PUBKEY(UINT64 *offset, BYTE *blob, TCPA_PUBKEY *pubKey)
{
	TSS_RESULT result;

	if (!pubKey) {
		(void)Trspi_UnloadBlob_KEY_PARMS(offset, blob, NULL);
		(void)Trspi_UnloadBlob_STORE_PUBKEY(offset, blob, NULL);

		return TSS_SUCCESS;
	}

	if ((result = Trspi_UnloadBlob_KEY_PARMS(offset, blob, &pubKey->algorithmParms)))
		return result;
	if ((result = Trspi_UnloadBlob_STORE_PUBKEY(offset, blob, &pubKey->pubKey))) {
		free(pubKey->pubKey.key);
		free(pubKey->algorithmParms.parms);
		pubKey->pubKey.key = NULL;
		pubKey->pubKey.keyLength = 0;
		pubKey->algorithmParms.parms = NULL;
		pubKey->algorithmParms.parmSize = 0;
		return result;
	}

	return TSS_SUCCESS;
}
