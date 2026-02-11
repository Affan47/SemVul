GetLayerForVTable(const char* pszVTableName)
{
    std::map<CPLString, OGRLayer*>::iterator oIter =
        oMapVTableToOGRLayer.find(pszVTableName);
    if( oIter == oMapVTableToOGRLayer.end() )
        return NULL;

    OGRLayer* poLayer = oIter->second;
    if( poLayer == NULL )
    {


        if( sqlite3_exec(hDB,
                     CPLSPrintf("PRAGMA table_info(\"%s\")",
                                OGRSQLiteEscapeName(pszVTableName).c_str()),
                     NULL, NULL, NULL) == SQLITE_OK )
        {
            poLayer = oMapVTableToOGRLayer[pszVTableName];
        }
    }

    return poLayer;
}
