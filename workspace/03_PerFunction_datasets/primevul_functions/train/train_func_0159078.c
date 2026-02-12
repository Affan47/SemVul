uchar*  rsCStrGetSzStr(cstr_t *pThis)
{
	size_t i;

	rsCHECKVALIDOBJECT(pThis, OIDrsCStr);

	if(pThis->pBuf != NULL)
		if(pThis->pszBuf == NULL) {

			if((pThis->pszBuf = malloc((pThis->iStrLen + 1) * sizeof(uchar))) == NULL) {


			}
			else {


				for(i = 0 ; i < pThis->iStrLen ; ++i) {
					if(pThis->pBuf[i] == '\0')
						pThis->pszBuf[i] = ' ';
					else
						pThis->pszBuf[i] = pThis->pBuf[i];
				}

				pThis->pszBuf[i] = '\0';
			}
		}

	return(pThis->pszBuf);
}
