static void mdbReleaseStmt( MySqlObj *jdb, MysqlPrep *prep, int discard ) {
    if( jdb->maxStmts<=0 || discard ) {

        mdbRelease1Stmt(jdb, prep);
    } else {

        if (!prep->elPtr)
            prep->elPtr = Jsi_ListPushFrontNew(jdb->stmtCache, prep);
        else
            Jsi_ListPushFront(jdb->stmtCache, prep->elPtr);
        mdbStmtLimit(jdb);
    }
}
