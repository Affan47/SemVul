list2vec(std::vector<double> &v,const char *pszList)
{
    if ((pszList==NULL)||(pszList[0]==0)) return;
    char **papszTokens=CSLTokenizeString2(pszList," \t\n\r",
        CSLT_STRIPLEADSPACES|CSLT_STRIPENDSPACES);
    v.clear();
    for (int i=0;i<CSLCount(papszTokens);i++)
        v.push_back(CPLStrtod(papszTokens[i],NULL));
    CSLDestroy(papszTokens);
}
