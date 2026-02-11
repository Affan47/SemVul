DSAU_ConvertSignedToFixedUnsigned(SECItem *dest, SECItem *src)
{
    unsigned char *pSrc = src->data;
    unsigned char *pDst = dest->data;
    unsigned int   cntSrc = src->len;
    unsigned int   cntDst = dest->len;
    int            zCount = cntDst - cntSrc;

    if (zCount > 0) {
    	PORT_Memset(pDst, 0, zCount);
	PORT_Memcpy(pDst + zCount, pSrc, cntSrc);
	return SECSuccess;
    }
    if (zCount <= 0) {

	while (zCount++ < 0) {
	    if (*pSrc++ != 0)
		goto loser;
	}
    }
    PORT_Memcpy(pDst, pSrc, cntDst);
    return SECSuccess;

loser:
    PORT_SetError( PR_INVALID_ARGUMENT_ERROR );
    return SECFailure;
}
