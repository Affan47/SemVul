_AVCBinReadRepairDBFFieldName(char *pszFieldName)
{
    char *pszTmp;

    if ((pszTmp = strrchr(pszFieldName, '_')) == NULL)
        return;


    if (EQUAL(pszTmp, "_"))
        *pszTmp = '#';
    else if (EQUAL(pszTmp, "_ID"))
        *pszTmp = '-';

}
