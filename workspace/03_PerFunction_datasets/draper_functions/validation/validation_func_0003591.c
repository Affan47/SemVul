SoftRollback()

{
    if( nSoftTransactionLevel <= 0 )
    {
        CPLDebug( "OGR_SQLITE", "SoftRollback() with no transaction active." );
        return OGRERR_FAILURE;
    }

    nSoftTransactionLevel = 0;

    int rc;
    char *pszErrMsg;

#ifdef DEBUG
    CPLDebug( "OGR_SQLITE", "ROLLBACK Transaction" );
#endif

    rc = sqlite3_exec( hDB, "ROLLBACK", NULL, NULL, &pszErrMsg );
    if( rc != SQLITE_OK )
    {
        CPLError( CE_Failure, CPLE_AppDefined,
                  "ROLLBACK transaction failed: %s",
                  pszErrMsg );
        sqlite3_free( pszErrMsg );
        return OGRERR_FAILURE;
    }

    for(int i = 0; i < nLayers; i++)
        papoLayers[i]->InvalidateCachedFeatureCountAndExtent();

    return OGRERR_NONE;
}
