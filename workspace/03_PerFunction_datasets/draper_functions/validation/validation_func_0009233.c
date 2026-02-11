startElementDefault(const char *pszName,
                                           const char **ppszAttr)
{
    if (strcmp(pszName, "table:table") == 0)
    {
        const char* pszTableName =
            GetAttributeValue(ppszAttr, "table:name", "unnamed");

        poCurLayer = new OGRODSLayer(this, pszTableName);
        papoLayers = (OGRLayer**)CPLRealloc(papoLayers, (nLayers + 1) * sizeof(OGRLayer*));
        papoLayers[nLayers++] = poCurLayer;

        nCurLine = 0;
        nEmptyRowsAccumulated = 0;
        apoFirstLineValues.resize(0);
        apoFirstLineTypes.resize(0);
        PushState(STATE_TABLE);
        bEndTableParsing = FALSE;
    }
}
