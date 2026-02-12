static Jsi_RC dbPrepareStmt(
    Jsi_Db *jdb,
    char const *zIn,
    char const **pzOut,
    SqlPreparedStmt **ppPreStmt
) {
    const char *zSql = zIn;
    sqlite3_stmt *pStmt;
    SqlPreparedStmt *pPreStmt = 0;


    Jsi_RC rc = JSI_OK;
    Jsi_Interp *interp = jdb->interp;
    JSI_NOTUSED(interp);

    *ppPreStmt = 0;


    while( isspace(zSql[0]) ) {
        zSql++;
    }

    Jsi_HashEntry *entry = Jsi_HashEntryFind(jdb->stmtHash, zSql);
    if (entry && ((pPreStmt = (SqlPreparedStmt*)Jsi_HashValueGet(entry)))) {

        if (jdb->debug & TMODE_PREPARE)
            JSI_DBQUERY_PRINTF( "DEBUG: prepare cache-hit: %s\n", zSql);
        pStmt = pPreStmt->pStmt;
        *pzOut = &zSql[pPreStmt->nSql];


        Jsi_ListPop(jdb->stmtCache, pPreStmt->elPtr);
        jdb->stmtCacheCnt = Jsi_ListSize(jdb->stmtCache);

    }


    if( pPreStmt==0 ) {
        int nByte;

        if( SQLITE_OK!=sqlite3_prepare_v2(jdb->db, zSql, -1, &pStmt, pzOut) )

            return Jsi_LogError("PREPARE: %s", sqlite3_errmsg(jdb->db));
        if( pStmt==0 ) {
            if( SQLITE_OK!=sqlite3_errcode(jdb->db) ) {

                Jsi_LogError("PREP: %s", sqlite3_errmsg(jdb->db));
                return JSI_ERROR;
            } else {


                return JSI_OK;
            }
        }

        if (jdb->debug & TMODE_PREPARE)
            JSI_DBQUERY_PRINTF( "DEBUG: prepare new: %s\n", zSql);
        assert( pPreStmt==0 );

        jdb->stmtCacheCnt++;
        nByte = sizeof(SqlPreparedStmt);
        pPreStmt = (SqlPreparedStmt*)Jsi_Calloc(1, nByte);
        pPreStmt->sig = SQLITE_SIG_STMT;

        pPreStmt->pStmt = pStmt;
        pPreStmt->nSql = (*pzOut - zSql);
        pPreStmt->zSql = sqlite3_sql(pStmt);
        bool isNew = 0;
        pPreStmt->entry = Jsi_HashEntryNew(jdb->stmtHash, zSql, &isNew);
        if (!isNew)
            JSI_DBQUERY_PRINTF( "sqlite dup stmt entry");
        Jsi_HashValueSet(pPreStmt->entry, pPreStmt);


    }
    assert( pPreStmt );
    assert( Jsi_Strlen(pPreStmt->zSql)==pPreStmt->nSql );
    assert( 0==memcmp(pPreStmt->zSql, zSql, pPreStmt->nSql) );
    *ppPreStmt = pPreStmt;

    return rc;
}
