static void dbReleaseStmt(
    Jsi_Db *jdb,
    SqlPreparedStmt *pPreStmt,
    int discard
) {


    if( jdb->stmtCacheMax<=0 || discard ) {

        dbPrepStmtFree(jdb, pPreStmt);
    } else {

        if (!pPreStmt->elPtr)
            pPreStmt->elPtr = Jsi_ListPushFrontNew(jdb->stmtCache, pPreStmt);
        else
            Jsi_ListPushFront(jdb->stmtCache, pPreStmt->elPtr);
        dbPrepStmtLimit(jdb);
        jdb->stmtCacheCnt = Jsi_ListSize(jdb->stmtCache);
    }
}
