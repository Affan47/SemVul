UnloadBlob_CERTIFY_INFO(UINT64 *offset, BYTE *blob, TCPA_CERTIFY_INFO *certify)
{
	TSS_RESULT rc;

	if (!certify) {
		TPM_VERSION version;
		UINT32 size;

		UnloadBlob_VERSION(offset, blob, &version);
		UnloadBlob_UINT16(offset, NULL, blob);
		UnloadBlob_KEY_FLAGS(offset, blob, NULL);
		UnloadBlob_BOOL(offset, NULL, blob);

		if ((rc = UnloadBlob_KEY_PARMS(offset, blob, NULL)))
			return rc;

		UnloadBlob(offset, TCPA_DIGEST_SIZE, blob, NULL);
		UnloadBlob(offset, TCPA_NONCE_SIZE, blob, NULL);
		UnloadBlob_BOOL(offset, NULL, blob);
		UnloadBlob_UINT32(offset, &size, blob);

		if (size > 0)
			UnloadBlob(offset, size, blob, NULL);

		if (Decode_UINT16((BYTE *) &version) == TPM_TAG_CERTIFY_INFO2){


			UnloadBlob_UINT32(offset, &size, blob);
			if (size > 0)
				UnloadBlob(offset, size, blob, NULL);
		}

		return TSS_SUCCESS;
	}

	UnloadBlob_VERSION(offset, blob, (TPM_VERSION *)&certify->version);
	UnloadBlob_UINT16(offset, &certify->keyUsage, blob);
	UnloadBlob_KEY_FLAGS(offset, blob, &certify->keyFlags);
	UnloadBlob_BOOL(offset, (TSS_BOOL *)&certify->authDataUsage, blob);

	if ((rc = UnloadBlob_KEY_PARMS(offset, blob, &certify->algorithmParms)))
		return rc;

	UnloadBlob(offset, TCPA_DIGEST_SIZE, blob, certify->pubkeyDigest.digest);
	UnloadBlob(offset, TCPA_NONCE_SIZE, blob, certify->data.nonce);
	UnloadBlob_BOOL(offset, (TSS_BOOL *)&certify->parentPCRStatus, blob);
	UnloadBlob_UINT32(offset, &certify->PCRInfoSize, blob);

	if (certify->PCRInfoSize > 0) {
		certify->PCRInfo = (BYTE *)malloc(certify->PCRInfoSize);
		if (certify->PCRInfo == NULL) {
			LogError("malloc of %u bytes failed.", certify->PCRInfoSize);
			certify->PCRInfoSize = 0;
			free(certify->algorithmParms.parms);
			certify->algorithmParms.parms = NULL;
			certify->algorithmParms.parmSize = 0;
			return TCSERR(TSS_E_OUTOFMEMORY);
		}
		UnloadBlob(offset, certify->PCRInfoSize, blob, certify->PCRInfo);
	} else {
		certify->PCRInfo = NULL;
	}

	if (Decode_UINT16((BYTE *) &certify->version) == TPM_TAG_CERTIFY_INFO2){


		UINT32 size;
		UnloadBlob_UINT32(offset, &size, blob);
		if (size > 0)
			UnloadBlob(offset, size, blob, NULL);
	}

	return TSS_SUCCESS;
}
