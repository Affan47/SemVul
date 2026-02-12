PssDecode(
	  TPM_ALG_ID   hashAlg,
	  TPM2B       *dIn,
	  TPM2B       *eIn
	  )
{
    UINT32           hLen = CryptHashGetDigestSize(hashAlg);
    BYTE             mask[MAX_RSA_KEY_BYTES];
    BYTE            *pm = mask;
    BYTE            *pe;
    BYTE             pad[8] = {0};
    UINT32           i;
    UINT32           mLen;
    BYTE             fail;
    TPM_RC           retVal = TPM_RC_SUCCESS;
    HASH_STATE       hashState;

    pAssert(dIn != NULL && eIn != NULL);
    pe = eIn->buffer;

    if(hLen == 0)
	ERROR_RETURN(TPM_RC_SCHEME);

    fail = pe[0] & 0x80;

    fail |= pe[eIn->size - 1] ^ 0xbc;


    mLen = eIn->size - hLen - 1;
    CryptMGF1(mLen, mask, hashAlg, hLen, &pe[mLen]);

    mask[0] &= 0x7F;
    pAssert(mLen <= sizeof(mask));


    for(i = mLen; i > 0; i--)
	*pm++ ^= *pe++;

    for(pm = mask, i = mLen; i > 0; i--)
	{
	    if(*pm == 0x01)
		break;
	    else
		fail |= *pm++;
	}

    fail |= (i == 0);


    if(fail)
	{
	    i = mLen;
	    pm = mask;
	}
    else
	{
	    pm++;
	    i--;
	}


    CryptHashStart(&hashState, hashAlg);

    CryptDigestUpdate(&hashState, 8, pad);

    CryptDigestUpdate(&hashState, dIn->size, dIn->buffer);

    CryptDigestUpdate(&hashState, i, pm);

    fail |= (CryptHashEnd(&hashState, hLen, mask) != hLen);

    for(pm = mask; hLen > 0; hLen--)


	fail |= *pm++ ^ *pe++;
    retVal = (fail != 0) ? TPM_RC_VALUE : TPM_RC_SUCCESS;
 Exit:
    return retVal;
}
