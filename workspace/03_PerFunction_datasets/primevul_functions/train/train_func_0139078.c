query_int(const struct lsqlite3_private * lsqlite3,
          long long * pRet,
          const char * pSql,
          ...)
{
        int             ret;
        int             bLoop;
        char *          p;
        sqlite3_stmt *  pStmt;
        va_list         args;


        va_start(args, pSql);


        if ((p = sqlite3_vmprintf(pSql, args)) == NULL) {
		va_end(args);
                return SQLITE_NOMEM;
        }


        for (bLoop = TRUE; bLoop; ) {


                if ((ret = sqlite3_prepare(lsqlite3->sqlite,
                                           p,
                                           -1,
                                           &pStmt,
                                           NULL)) == SQLITE_SCHEMA) {
                        if (stmtGetEID != NULL) {
                                sqlite3_finalize(stmtGetEID);
                                stmtGetEID = NULL;
                        }
                        continue;
                } else if (ret != SQLITE_OK) {
                        break;
                }


                if ((ret = sqlite3_step(pStmt)) == SQLITE_SCHEMA) {
                        if (stmtGetEID != NULL) {
                                sqlite3_finalize(stmtGetEID);
                                stmtGetEID = NULL;
                        }
                        (void) sqlite3_finalize(pStmt);
                        continue;
                } else if (ret != SQLITE_ROW) {
                        (void) sqlite3_finalize(pStmt);
                        break;
                }


                *pRet = sqlite3_column_int64(pStmt, 0);


                if ((ret = sqlite3_finalize(pStmt)) == SQLITE_SCHEMA) {
                        if (stmtGetEID != NULL) {
                                sqlite3_finalize(stmtGetEID);
                                stmtGetEID = NULL;
                        }
                        continue;
                } else if (ret != SQLITE_OK) {
                        (void) sqlite3_finalize(pStmt);
                        break;
                }


                bLoop = FALSE;
        }


        va_end(args);


        sqlite3_free(p);

        return ret;
}
