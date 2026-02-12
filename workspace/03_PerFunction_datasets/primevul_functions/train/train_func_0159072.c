int rsCStrCaseInsensitveStartsWithSzStr(cstr_t *pCS1, uchar *psz, size_t iLenSz)
{
	register size_t i;

	rsCHECKVALIDOBJECT(pCS1, OIDrsCStr);
	assert(psz != NULL);
	assert(iLenSz == strlen((char*)psz));
	if(pCS1->iStrLen >= iLenSz) {


		if(iLenSz == 0)
			return 0;
		else {
			for(i = 0 ; i < iLenSz ; ++i) {
				if(tolower(pCS1->pBuf[i]) != tolower(psz[i]))
					return tolower(pCS1->pBuf[i]) - tolower(psz[i]);
			}

			return 0;
		}
	}
	else
		return -1;
}
