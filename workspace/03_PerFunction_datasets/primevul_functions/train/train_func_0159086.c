int rsCStrOffsetSzStrCmp(cstr_t *pCS1, size_t iOffset, uchar *psz, size_t iLenSz)
{
	BEGINfunc
	rsCHECKVALIDOBJECT(pCS1, OIDrsCStr);
	assert(iOffset < pCS1->iStrLen);
	assert(psz != NULL);
	assert(iLenSz == strlen((char*)psz));
	if((pCS1->iStrLen - iOffset) == iLenSz) {


		if(iLenSz == 0) {
			return 0;
			ENDfunc
		} else {


			register size_t i;
			for(i = 0 ; i < iLenSz ; ++i) {
				if(pCS1->pBuf[i+iOffset] != psz[i])
					return pCS1->pBuf[i+iOffset] - psz[i];
			}

			return 0;
			ENDfunc
		}
	}
	else {
		return pCS1->iStrLen - iOffset - iLenSz;
		ENDfunc
	}
}
