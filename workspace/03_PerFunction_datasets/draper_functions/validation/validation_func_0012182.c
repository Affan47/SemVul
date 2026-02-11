CSLTokenizeStringComplex( const char * pszString,
                                  const char * pszDelimiters,
                                  int bHonourStrings, int bAllowEmptyTokens )

{
    char	**papszRetList = NULL;
    char 	*pszToken;
    int		nTokenMax, nTokenLen;

    pszToken = (char *) CPLCalloc(10,1);
    nTokenMax = 10;

    while( pszString != NULL && *pszString != '\0' )
    {
        int	bInString = FALSE;

        nTokenLen = 0;


        for( ; *pszString != '\0'; pszString++ )
        {


            if( !bInString && strchr(pszDelimiters, *pszString) != NULL )
            {
                pszString++;
                break;
            }


            if( bHonourStrings && *pszString == '"' )
            {
                if( bInString )
                {
                    bInString = FALSE;
                    continue;
                }
                else
                {
                    bInString = TRUE;
                    continue;
                }
            }


            if( bInString && pszString[0] == '\\' && pszString[1] == '"' )
            {
                pszString++;
            }


            else if( bInString
                     && pszString[0] == '\\' && pszString[1] == '\\' )
            {
                pszString++;
            }

            if( nTokenLen >= nTokenMax-1 )
            {
                nTokenMax = nTokenMax * 2 + 10;
                pszToken = (char *) CPLRealloc( pszToken, nTokenMax );
            }

            pszToken[nTokenLen] = *pszString;
            nTokenLen++;
        }

        pszToken[nTokenLen] = '\0';

        if( pszToken[0] != '\0' || bAllowEmptyTokens )
        {
            papszRetList = CSLAddString( papszRetList, pszToken );
        }


        if ( *pszString == '\0' && bAllowEmptyTokens &&
             strchr(pszDelimiters, *(pszString-1)) )
        {
            papszRetList = CSLAddString( papszRetList, "" );
        }
    }

    if( papszRetList == NULL )
        papszRetList = (char **) CPLCalloc(sizeof(char *),1);

    CPLFree( pszToken );

    return papszRetList;
}
