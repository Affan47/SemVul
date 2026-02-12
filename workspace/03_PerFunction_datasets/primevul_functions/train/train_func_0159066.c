rsRetVal rsCStrTruncate(cstr_t *pThis, size_t nTrunc)
{
	rsCHECKVALIDOBJECT(pThis, OIDrsCStr);

	if(pThis->iStrLen < nTrunc)
		return RS_TRUNCAT_TOO_LARGE;

	pThis->iStrLen -= nTrunc;

	if(pThis->pszBuf != NULL) {


		 pThis->pszBuf[pThis->iStrLen] = '\0';
	}

	return RS_RET_OK;
}
