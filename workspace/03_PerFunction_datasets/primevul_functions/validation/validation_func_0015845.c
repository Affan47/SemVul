RSASSA_Decode(
	      TPM_ALG_ID       hashAlg,
	      TPM2B           *hIn,
	      TPM2B           *eIn
	      )
{
    BYTE             fail;
    const BYTE      *der;
    BYTE            *pe;
    INT32            derSize = CryptHashGetDer(hashAlg, &der);
    INT32            hashSize = CryptHashGetDigestSize(hashAlg);
    INT32            fillSize;
    TPM_RC           retVal;
    BYTE            *digest;
    UINT16           digestSize;
    pAssert(hIn != NULL && eIn != NULL);
    pe = eIn->buffer;


    if(derSize == 0 || (unsigned)hashSize != hIn->size)
	ERROR_RETURN(TPM_RC_SCHEME);


    fillSize = eIn->size - derSize - hashSize - 3;


    fail = *pe++;
    fail |= *pe++ ^ 1;
    for(; fillSize > 0; fillSize--)
	fail |= *pe++ ^ 0xff;
    fail |= *pe++;
    for(; derSize > 0; derSize--)
	fail |= *pe++ ^ *der++;
    digestSize = hIn->size;
    digest = hIn->buffer;
    for(; digestSize > 0; digestSize--)
	fail |= *pe++ ^ *digest++;
    retVal = (fail != 0) ? TPM_RC_VALUE : TPM_RC_SUCCESS;
 Exit:
    return retVal;
}
