char *_q_urlencode(const void *bin, size_t size)
{
    const char URLCHARTBL[256] = {
        0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,
        0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,
        0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,'-','.','/',
        '0','1','2','3','4','5','6','7','8','9',':', 0 , 0 , 0 , 0 , 0 ,
        '@','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O',
        'P','Q','R','S','T','U','V','W','X','Y','Z', 0 ,'\\',0 , 0 ,'_',
        0 ,'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o',
        'p','q','r','s','t','u','v','w','x','y','z', 0 , 0 , 0 , 0 , 0 ,
        0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,
        0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,
        0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,
        0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,
        0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,
        0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,
        0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,
        0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0
    };

    if (bin == NULL) return NULL;
    if (size == 0) return strdup("");


    char *pszEncStr = (char *)malloc((size * 3) + 1);
    if (pszEncStr == NULL) return NULL;

    char *pszEncPt = pszEncStr;
    char *pBinPt = (char *)bin;
    const char *pBinEnd = (bin + size - 1);
    for (; pBinPt <= pBinEnd; pBinPt++) {
        if (URLCHARTBL[(int)(*pBinPt)] != 0) {
            *pszEncPt++ = *pBinPt;
        } else {
            unsigned char cUpper4 = (*pBinPt >> 4);
            unsigned char cLower4 = (*pBinPt & 0x0F);

            *pszEncPt++ = '%';
            *pszEncPt++ = (cUpper4 < 0x0A) ? (cUpper4 + '0') : ((cUpper4 - 0x0A) + 'a');
            *pszEncPt++ = (cLower4 < 0x0A) ? (cLower4 + '0') : ((cLower4 - 0x0A) + 'a');
        }
    }
    *pszEncPt = '\0';

    return pszEncStr;
}
