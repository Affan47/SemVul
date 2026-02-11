ajDebugTest(const char* token)
{
    AjPStr filename = NULL;
    const char* debugtestname = ".debugtest";
    char* ctoken = NULL;
    AjPStr line = NULL;
    AjPStr strtoken = NULL;
    AjPStr rest = NULL;
    static ajint depth    = 0;

    struct
    {
        ajuint count;
        ajuint max;
    } *stats;

    if(depth)
        return ajFalse;

    depth++;

    if(!messDebugTestInit)
    {
        filename = ajStrNewC(debugtestname);

        if(ajFilenameExists(filename))
        {
            messDebugTestFile = ajFileNewInNameS(filename);
        }
        else
        {
            ajFmtPrintS(&filename, "%s%s%s",
                        getenv("HOME"), SLASH_STRING, debugtestname);
            if(ajFilenameExists(filename))
                messDebugTestFile = ajFileNewInNameS(filename);
        }
        ajStrDel(&filename);

        if(messDebugTestFile)
        {
            messDebugTestTable = ajTablecharNew(256);

            while(ajReadlineTrim(messDebugTestFile, &line))
            {
                if(!ajStrCutComments(&line))
                    continue;
                if(ajStrExtractFirst(line, &rest, &strtoken))
                {
                    AJNEW0(stats);
                    ctoken = ajCharNewS(strtoken);
                    if(ajStrIsInt(rest))
                        ajStrToUint(rest, &stats->max);
                    else
                        stats->max = UINT_MAX;

                    ajTablePut(messDebugTestTable, ctoken, stats);
                    ctoken = NULL;
                    stats = NULL;
                }
            }

            ajStrDel(&line);
            ajStrDel(&strtoken);
            ajStrDel(&rest);
            ajFileClose(&messDebugTestFile);
        }
        messDebugTestInit = ajTrue;
     }

    depth--;

    if(!messDebugTestTable)
        return ajFalse;

    depth++;
    stats = ajTableFetchmodC(messDebugTestTable, token);
    depth--;


    if(!stats)
        return ajFalse;

    if(!stats->max)
        return ajTrue;

    if(stats->count++ >= stats->max)
        return ajFalse;

    return ajTrue;
}
