static int parseRFCField(uchar **pp2parse, uchar *pResult, int *pLenStr)
{
	uchar *p2parse;
	int iRet = 0;

	assert(pp2parse != NULL);
	assert(*pp2parse != NULL);
	assert(pResult != NULL);

	p2parse = *pp2parse;


	while(*pLenStr > 0  && *p2parse != ' ') {
		*pResult++ = *p2parse++;
		--(*pLenStr);
	}

	if(*pLenStr > 0 && *p2parse == ' ') {
		++p2parse;
		--(*pLenStr);
	} else {
		iRet = 1;
	}
	*pResult = '\0';


	*pp2parse = p2parse;
	return 0;
}
