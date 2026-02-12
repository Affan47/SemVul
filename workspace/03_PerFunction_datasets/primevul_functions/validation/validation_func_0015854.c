RSASSA_Encode(
	      TPM2B               *pOut,

	      TPM_ALG_ID           hashAlg,
	      TPM2B               *hIn
	      )
{
    const BYTE      *der;
    BYTE            *eOut;
    INT32            derSize = CryptHashGetDer(hashAlg, &der);
    INT32            fillSize;
    TPM_RC           retVal = TPM_RC_SUCCESS;

    if(derSize == 0)
	ERROR_RETURN(TPM_RC_SCHEME);


    if(CryptHashGetDigestSize(hashAlg) != hIn->size)
	ERROR_RETURN(TPM_RC_VALUE);
    fillSize = pOut->size - derSize - hIn->size - 3;
    eOut = pOut->buffer;

    if(fillSize < 8)
	ERROR_RETURN(TPM_RC_SIZE);

    *eOut++ = 0;
    *eOut++ = 1;
    for(; fillSize > 0; fillSize--)
	*eOut++ = 0xff;
    *eOut++ = 0;
    for(; derSize > 0; derSize--)
	*eOut++ = *der++;
    der = hIn->buffer;
    for(fillSize = hIn->size; fillSize > 0; fillSize--)
	*eOut++ = *der++;
 Exit:
    return retVal;
}
