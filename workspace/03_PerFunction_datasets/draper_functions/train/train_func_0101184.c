DBFIsAttributeNULL( DBFHandle psDBF, int iRecord, int iField )

{
    const char	*pszValue;

    pszValue = DBFReadStringAttribute( psDBF, iRecord, iField );

    if( pszValue == NULL )
        return TRUE;

    switch(psDBF->pachFieldType[iField])
    {
      case 'N':
      case 'F':

        return pszValue[0] == '*';

      case 'D':

        return (strncmp(pszValue,"00000000",8) == 0 || strlen(pszValue) == 0);

      case 'L':

        return pszValue[0] == '?';

      default:

        return strlen(pszValue) == 0;
    }
}
