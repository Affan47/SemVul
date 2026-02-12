OaepDecode(
	   TPM2B           *dataOut,
	   TPM_ALG_ID       hashAlg,
	   const TPM2B     *label,
	   TPM2B           *padded
	   )
{
    UINT32       i;
    BYTE         seedMask[MAX_DIGEST_SIZE];
    UINT32       hLen = CryptHashGetDigestSize(hashAlg);
    BYTE         mask[MAX_RSA_KEY_BYTES];
    BYTE        *pp;
    BYTE        *pm;
    TPM_RC       retVal = TPM_RC_SUCCESS;


    if((padded->size < (unsigned)((2 * hLen) + 2)) || (padded->buffer[0] != 0))
	ERROR_RETURN(TPM_RC_VALUE);


    CryptMGF1(hLen, seedMask, hashAlg, padded->size - hLen - 1,
	      &padded->buffer[hLen + 1]);

    pAssert(hLen <= sizeof(seedMask));
    pp = &padded->buffer[1];
    pm = seedMask;
    for(i = hLen; i > 0; i--)
	*pm++ ^= *pp++;

    CryptMGF1(padded->size - hLen - 1, mask, hashAlg, hLen, seedMask);

    pp = &padded->buffer[hLen + 1];
    pm = mask;
    for(i = (padded->size - hLen - 1); i > 0; i--)
	*pm++ ^= *pp++;


    if((CryptHashBlock(hashAlg, label->size, (BYTE *)label->buffer,
		       hLen, seedMask)) != hLen)
	FAIL(FATAL_ERROR_INTERNAL);
    if(memcmp(seedMask, mask, hLen) != 0)
	ERROR_RETURN(TPM_RC_VALUE);

    pm = &mask[hLen];
    for(i = (UINT32)padded->size - (2 * hLen) - 1; i > 0; i--)
	{
	    if(*pm++ != 0)
		break;
	}

    if(i == 0 || pm[-1] != 0x01)
	ERROR_RETURN(TPM_RC_VALUE);


    i--;
    if(i > dataOut->size)

	return TPM_RC_VALUE;
    memcpy(dataOut->buffer, pm, i);
    dataOut->size = (UINT16)i;
 Exit:
    if(retVal != TPM_RC_SUCCESS)
	dataOut->size = 0;
    return retVal;
}
