BOOL ValidateOpensslSignature(BYTE* pbBuffer, DWORD dwBufferLen, BYTE* pbSignature, DWORD dwSigLen)
{
	HCRYPTPROV hProv = 0;
	HCRYPTHASH hHash = 0;
	HCRYPTKEY hPubKey;

	RSA_2048_PUBKEY pbMyPubKey = {
		{ PUBLICKEYBLOB, CUR_BLOB_VERSION, 0, CALG_RSA_KEYX },


		{ 0x31415352, sizeof(pbMyPubKey.Modulus) * 8, 0x010001 },
		{ 0 }
	};
	USHORT dwMyPubKeyLen = sizeof(pbMyPubKey);
	BOOL r;
	BYTE t;
	int i, j;


	r = CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_AES, CRYPT_NEWKEYSET | CRYPT_VERIFYCONTEXT);
	if (!r) {
		uprintf("PKI: Could not create the default key container: %s", WinPKIErrorString());
		goto out;
	}


	assert(sizeof(rsa_pubkey_modulus) >= sizeof(pbMyPubKey.Modulus));
	for (i = 0; i < sizeof(pbMyPubKey.Modulus); i++)
		pbMyPubKey.Modulus[i] = rsa_pubkey_modulus[sizeof(rsa_pubkey_modulus) -1 - i];


	r = CryptImportKey(hProv, (BYTE*)&pbMyPubKey.BlobHeader, dwMyPubKeyLen, 0, 0, &hPubKey);
	if (!r) {
		uprintf("PKI: Could not import public key: %s", WinPKIErrorString());
		goto out;
	}


	r = CryptCreateHash(hProv, CALG_SHA_256, 0, 0, &hHash);
	if (!r) {
		uprintf("PKI: Could not create empty hash: %s", WinPKIErrorString());
		goto out;
	}


	r = CryptHashData(hHash, pbBuffer, dwBufferLen, 0);
	if (!r) {
		uprintf("PKI: Could not hash data: %s", WinPKIErrorString());
		goto out;
	}


	for (i = 0, j = dwSigLen - 1; i < j; i++, j--) {
		t = pbSignature[i];
		pbSignature[i] = pbSignature[j];
		pbSignature[j] = t;
	}


	r = CryptVerifySignature(hHash, pbSignature, dwSigLen, hPubKey, NULL, 0);
	if (!r) {


		memset(pbBuffer, 0, dwBufferLen);
		uprintf("Signature validation failed: %s", WinPKIErrorString());
	}

out:
	if (hHash)
		CryptDestroyHash(hHash);
	if (hProv)
		CryptReleaseContext(hProv, 0);
	return r;
}
