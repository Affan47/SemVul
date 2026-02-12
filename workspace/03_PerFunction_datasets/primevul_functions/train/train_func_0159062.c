rsCStrConvertToNumber(cstr_t *pStr, number_t *pNumber)
{
	DEFiRet;
	number_t n;
	int bIsNegative;
	size_t i;

	ASSERT(pStr != NULL);
	ASSERT(pNumber != NULL);

	if(pStr->iStrLen == 0) {

		pNumber = 0;
		FINALIZE;
	}


	for(i = 0 ; i < pStr->iStrLen && isspace(pStr->pBuf[i]) ; ++i) {

	}


	if(pStr->pBuf[i] == '+') {
		++i;
		bIsNegative = 0;
	} else if(pStr->pBuf[0] == '-') {
		++i;
		bIsNegative = 1;
	} else {
		bIsNegative = 0;
	}


	n = 0;
	while(i < pStr->iStrLen && isdigit(pStr->pBuf[i])) {
		n = n * 10 + pStr->pBuf[i] - '0';
		++i;
	}

	if(i < pStr->iStrLen)
		ABORT_FINALIZE(RS_RET_NOT_A_NUMBER);

	if(bIsNegative)
		n *= -1;


	*pNumber = n;

finalize_it:
	RETiRet;
}
