rsRetVal cstrConvSzStrAndDestruct(cstr_t *pThis, uchar **ppSz, int bRetNULL)
{
	DEFiRet;
	uchar* pRetBuf;

	rsCHECKVALIDOBJECT(pThis, OIDrsCStr);
	assert(ppSz != NULL);
	assert(bRetNULL == 0 || bRetNULL == 1);

	if(pThis->pBuf == NULL) {
		if(bRetNULL == 0) {
			CHKmalloc(pRetBuf = malloc(sizeof(uchar)));
			*pRetBuf = '\0';
		} else {
			pRetBuf = NULL;
		}
	} else
		pRetBuf = pThis->pBuf;

	*ppSz = pRetBuf;

finalize_it:


	RSFREEOBJ(pThis);
	RETiRet;
}
