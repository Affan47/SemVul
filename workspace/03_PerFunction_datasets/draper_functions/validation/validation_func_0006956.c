TAB_CSLLoad(const char *pszFname)
{
    FILE        *fp;
    const char  *pszLine;
    char        **papszStrList=NULL;

    fp = VSIFOpen(pszFname, "rt");

    if (fp)
    {
        while(!VSIFEof(fp))
        {
            if ( (pszLine = CPLReadLine(fp)) != NULL )
            {
                papszStrList = CSLAddString(papszStrList, pszLine);
            }
        }

        VSIFClose(fp);
    }

    return papszStrList;
}
