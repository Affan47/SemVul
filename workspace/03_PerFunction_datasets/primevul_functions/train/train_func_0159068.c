int rsCStrSzStrStartsWithCStr(cstr_t *pCS1, uchar *psz, size_t iLenSz)
{
	register int i;
	int iMax;

	rsCHECKVALIDOBJECT(pCS1, OIDrsCStr);
	assert(psz != NULL);
	assert(iLenSz == strlen((char*)psz));
	if(iLenSz >= pCS1->iStrLen) {


		iMax = pCS1->iStrLen;
		if(iMax == 0)
			return 0;
		else {
			for(i = 0 ; i < iMax ; ++i) {
				if(psz[i] != pCS1->pBuf[i])
					return psz[i] - pCS1->pBuf[i];
			}

			return 0;
		}
	}
	else
		return -1;
}
