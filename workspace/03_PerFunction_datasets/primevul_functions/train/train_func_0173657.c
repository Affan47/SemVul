static void dbEvalRowInfo(
    DbEvalContext *p,
    int *pnCol,
    char ***papColName,
    int **papColType
) {


    if( 0==p->apColName ) {
        sqlite3_stmt *pStmt = p->pPreStmt->pStmt;
        int i;
        int nCol;
        char **apColName = 0;
        int *apColType = 0;
        const char *zColName;
        int numRid = 0;

        p->nCol = nCol = sqlite3_column_count(pStmt);
        if( nCol>0 && (papColName || p->pArray) ) {
            int cnLen = sizeof(char*)*nCol, cnStart = cnLen;
            for(i=0; i<nCol && cnLen<sizeof(p->staticColNames); i++)
                cnLen += Jsi_Strlen(sqlite3_column_name(pStmt,i))+1;
            if (cnLen>=sizeof(p->staticColNames)) {
                apColName = (char**)Jsi_Calloc(nCol, sizeof(char*) );
                cnStart = 0;
            } else {
                apColName = (char**)p->staticColNames;
            }
            if (papColType) {
                if (nCol < SQL_MAX_STATIC_TYPES)
                    apColType = p->staticColTypes;
                else
                    apColType = (int*)Jsi_Calloc(nCol, sizeof(int));
            }
            for(i=0; i<nCol; i++) {
                zColName = sqlite3_column_name(pStmt,i);
                if (cnStart==0)
                    apColName[i] = Jsi_Strdup(zColName);
                else {
                    apColName[i] = p->staticColNames+cnStart;
                    Jsi_Strcpy(apColName[i], zColName);
                    cnStart += Jsi_Strlen(zColName)+1;
                }
                if (apColType)
                    apColType[i] = sqlite3_column_type(pStmt,i);

                if ((i == 0 || numRid>0) &&
                        (zColName[0] == 'r' && Jsi_Strcmp(zColName,"rowid") == 0)) {
                    numRid++;
                }
            }

            if (numRid > 1) {
                if (apColName != (char**)p->staticColNames) {
                    Jsi_Free(apColName[0]);
                    apColName[0] = Jsi_Strdup("oid");
                } else {
                    Jsi_Strcpy(apColName[0], "oid");
                }
            }
            p->apColName = apColName;
            p->apColType = apColType;
        }
    }
    if( papColName ) {
        *papColName = p->apColName;
    }
    if( papColType ) {
        *papColType = p->apColType;
    }
    if( pnCol ) {
        *pnCol = p->nCol;
    }
}
