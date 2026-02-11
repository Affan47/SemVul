ReadTHF(VSILFILE* fp)
{
    const char* pszLine;
    while((pszLine = CPLReadLine2L(fp, 81, NULL)) != NULL)
    {
        if (strlen(pszLine) < 8 || pszLine[7] != ':')
            continue;


        if (strncmp(pszLine, "LONSA", 5) == 0)
        {
            if (osLON.size() != 0)
            {
                CPLDebug("EDIGEO", "We only handle one lot per THF file");
                break;
            }
            osLON = pszLine + 8;
        }
        else if (strncmp(pszLine, "GNNSA", 5) == 0)
            osGNN = pszLine + 8;
        else if (strncmp(pszLine, "GONSA", 5) == 0)
            osGON = pszLine + 8;
        else if (strncmp(pszLine, "QANSA", 5) == 0)
            osQAN = pszLine + 8;
        else if (strncmp(pszLine, "DINSA", 5) == 0)
            osDIN = pszLine + 8;
        else if (strncmp(pszLine, "SCNSA", 5) == 0)
            osSCN = pszLine + 8;
        else if (strncmp(pszLine, "GDNSA", 5) == 0)
            aosGDN.push_back(pszLine + 8);
    }
    if (osLON.size() == 0)
    {
        CPLDebug("EDIGEO", "LON field missing");
        return 0;
    }
    if (osGON.size() == 0)
    {
        CPLDebug("EDIGEO", "GON field missing");
        return 0;
    }
    if (osDIN.size() == 0)
    {
        CPLDebug("EDIGEO", "DIN field missing");
        return 0;
    }
    if (osSCN.size() == 0)
    {
        CPLDebug("EDIGEO", "SCN field missing");
        return FALSE;
    }

    CPLDebug("EDIGEO", "LON = %s", osLON.c_str());
    CPLDebug("EDIGEO", "GNN = %s", osGNN.c_str());
    CPLDebug("EDIGEO", "GON = %s", osGON.c_str());
    CPLDebug("EDIGEO", "QAN = %s", osQAN.c_str());
    CPLDebug("EDIGEO", "DIN = %s", osDIN.c_str());
    CPLDebug("EDIGEO", "SCN = %s", osSCN.c_str());
    for(int i=0;i<(int)aosGDN.size();i++)
        CPLDebug("EDIGEO", "GDN[%d] = %s", i, aosGDN[i].c_str());

    return TRUE;
}
