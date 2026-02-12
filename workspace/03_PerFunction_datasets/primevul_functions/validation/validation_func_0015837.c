PssEncode(
	  TPM2B           *out,
	  TPM_ALG_ID       hashAlg,
	  TPM2B           *digest,
	  RAND_STATE      *rand
	  )
{
    UINT32               hLen = CryptHashGetDigestSize(hashAlg);
    BYTE                 salt[MAX_RSA_KEY_BYTES - 1];
    UINT16               saltSize;
    BYTE                *ps = salt;
    BYTE                *pOut;
    UINT16               mLen;
    HASH_STATE           hashState;

    pAssert(out != NULL && hLen > 0 && digest != NULL);

    mLen = (UINT16)(out->size - hLen - 1);

    saltSize = mLen - 1;

    if(saltSize > hLen)
	saltSize = (UINT16)hLen;


    pOut = out->buffer;
    memset(pOut, 0, 8);

    DRBG_Generate(rand, salt, saltSize);

    CryptHashStart(&hashState, hashAlg);
    CryptDigestUpdate(&hashState, 8, pOut);
    CryptDigestUpdate2B(&hashState, digest);
    CryptDigestUpdate(&hashState, saltSize, salt);
    CryptHashEnd(&hashState, hLen, &pOut[out->size - hLen - 1]);

    if(CryptMGF1(mLen, pOut, hashAlg, hLen, &pOut[mLen]) != mLen)
	FAIL(FATAL_ERROR_INTERNAL);


    *pOut &= 0x7f;

    pOut[out->size - 1] = 0xbc;

    pOut = &pOut[mLen - saltSize - 1];
    *pOut++ ^= 0x01;

    for(; saltSize > 0; saltSize--)
	*pOut++ ^= *ps++;

    return TPM_RC_SUCCESS;
}
