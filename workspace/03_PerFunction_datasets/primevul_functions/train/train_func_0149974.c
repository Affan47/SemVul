static int parseRFCStructuredData(uchar **pp2parse, uchar *pResult, int *pLenStr)
{
	uchar *p2parse;
	int bCont = 1;
	int iRet = 0;
	int lenStr;

	assert(pp2parse != NULL);
	assert(*pp2parse != NULL);
	assert(pResult != NULL);

	p2parse = *pp2parse;
	lenStr = *pLenStr;


	if(lenStr == 0 || *p2parse != '[')
		return 1;

	if(*p2parse == '-') {
		*pResult++ = '-';
		++p2parse;
		--lenStr;
	} else {
		while(bCont) {
			if(lenStr < 2) {

				if(lenStr > 0 && *p2parse == ']') {
					*pResult++ = *p2parse;
					p2parse++;
					lenStr--;
					bCont = 0;
				} else {
					iRet = 1;
					bCont = 0;
				}
			} else if(*p2parse == '\\' && *(p2parse+1) == ']') {

				*pResult++ = *p2parse++;
				*pResult++ = *p2parse++;
				lenStr -= 2;
			} else if(*p2parse == ']' && *(p2parse+1) == ' ') {

				*pResult++ = *p2parse;
				p2parse += 2;
				lenStr -= 2;
				bCont = 0;
			} else {
				*pResult++ = *p2parse++;
				--lenStr;
			}
		}
	}

	if(lenStr > 0 && *p2parse == ' ') {
		++p2parse;
		--lenStr;
	} else {
		iRet = 1;
	}
	*pResult = '\0';


	*pp2parse = p2parse;
	*pLenStr = lenStr;
	return 0;
}
