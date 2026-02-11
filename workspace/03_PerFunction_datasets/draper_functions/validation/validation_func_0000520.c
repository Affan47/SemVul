startElementRow(const char *pszName,
                                       const char **ppszAttr)
{
    if (strcmp(pszName, "c") == 0)
    {
        PushState(STATE_CELL);

        const char* pszR = GetAttributeValue(ppszAttr, "r", NULL);
        if (pszR)
        {

            int nNewCurCol = (pszR[0] - 'A');
            int i = 1;
            while(pszR[i] >= 'A' && pszR[i] <= 'Z')
            {
                nNewCurCol = nNewCurCol * 26 + (pszR[i] - 'A');
                i ++;
            }
            for(;nCurCol<nNewCurCol;nCurCol++)
            {
                apoCurLineValues.push_back("");
                apoCurLineTypes.push_back("");
            }
        }

        osValueType = "float";

        const char* pszS = GetAttributeValue(ppszAttr, "s", "-1");
        int nS = atoi(pszS);
        if (nS >= 0 && nS < (int)apoStyles.size())
        {
            OGRFieldType eType = apoStyles[nS];
            if (eType == OFTDateTime)
                osValueType = "datetime";
            else if (eType == OFTDate)
                osValueType = "date";
            else if (eType == OFTTime)
                osValueType = "time";
        }
        else if (nS != -1)
            CPLDebug("XLSX", "Cannot find style %d", nS);

        const char* pszT = GetAttributeValue(ppszAttr, "t", "");
        if ( EQUAL(pszT,"s"))
            osValueType = "stringLookup";
        else if( EQUAL(pszT,"inlineStr") )
            osValueType = "string";

        osValue = "";
    }
}
