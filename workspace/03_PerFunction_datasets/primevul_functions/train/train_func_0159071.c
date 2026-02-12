int rsCStrStartsWithSzStr(cstr_t *pCS1, uchar *psz, size_t iLenSz)
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
				if(pCS1->pBuf[i] != psz[i])
					return pCS1->pBuf[i] - psz[i];
			}

			return 0;
		}
	}
	else
		return -1;
}
