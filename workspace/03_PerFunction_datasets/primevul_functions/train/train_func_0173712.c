static void dbEvalFinalize(DbEvalContext *p) {


    if( p->pPreStmt ) {
        sqlite3_reset(p->pPreStmt->pStmt);
        dbReleaseStmt(p->jdb, p->pPreStmt, p->nocache);
        p->pPreStmt = 0;
    }
    if (p->dSql)
        Jsi_DSFree(p->dSql);
    dbReleaseColumnNames(p);
}
