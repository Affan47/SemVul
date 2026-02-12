OaepEncode(
	   TPM2B       *padded,
	   TPM_ALG_ID   hashAlg,
	   const TPM2B *label,
	   TPM2B       *message,
	   RAND_STATE  *rand
	   )
{
    INT32        padLen;
    INT32        dbSize;
    INT32        i;
    BYTE         mySeed[MAX_DIGEST_SIZE];
    BYTE        *seed = mySeed;
    INT32        hLen = CryptHashGetDigestSize(hashAlg);
    BYTE         mask[MAX_RSA_KEY_BYTES];
    BYTE        *pp;
    BYTE        *pm;
    TPM_RC       retVal = TPM_RC_SUCCESS;
    pAssert(padded != NULL && message != NULL);


    if(hLen <= 0)
	return TPM_RC_VALUE;


    if(padded->size < (2 * hLen) + 2)
	ERROR_RETURN(TPM_RC_HASH);

    if(message->size > (padded->size - (2 * hLen) - 2))
	ERROR_RETURN(TPM_RC_VALUE);


    pp = &padded->buffer[hLen + 1];
    if(CryptHashBlock(hashAlg, label->size, (BYTE *)label->buffer,
		      hLen, pp) != hLen)
	ERROR_RETURN(TPM_RC_FAILURE);

    padLen = padded->size - message->size - (2 * hLen) - 2;
    MemorySet(&pp[hLen], 0, padLen);
    pp[hLen + padLen] = 0x01;
    padLen += 1;
    memcpy(&pp[hLen + padLen], message->buffer, message->size);

    dbSize = hLen + padLen + message->size;


    CryptRandomGenerate(hLen, mySeed);
    DRBG_Generate(rand, mySeed, (UINT16)hLen);

    CryptMGF1(dbSize, mask, hashAlg, hLen, seed);

    pm = mask;
    for(i = dbSize; i > 0; i--)
	*pp++ ^= *pm++;
    pp = &padded->buffer[hLen + 1];

    if(CryptMGF1(hLen, &padded->buffer[1], hashAlg, dbSize, pp) != (unsigned)hLen)
	ERROR_RETURN(TPM_RC_VALUE);

    pp = &padded->buffer[1];
    pm = seed;
    for(i = hLen; i > 0; i--)
	*pp++ ^= *pm++;

    padded->buffer[0] = 0x00;
 Exit:
    return retVal;
}
