static Jsi_RC SqliteFunctionCmd(Jsi_Interp *interp, Jsi_Value *args, Jsi_Value *_this,
                             Jsi_Value **ret, Jsi_Func *funcPtr)
{
    SqlFunc *pFunc;
    Jsi_Value *tocall, *nVal;
    char *zName;
    int rc, nArg = -1, argc;
    argc = Jsi_ValueGetLength(interp, args);
    Jsi_Db *jdb;

    if (!(jdb = dbGetDbHandle(interp, _this, funcPtr))) return JSI_ERROR;

    zName = Jsi_ValueArrayIndexToStr(interp, args, 0, NULL);
    tocall = Jsi_ValueArrayIndex(interp, args, 1);
    if (zName == NULL)
        return Jsi_LogError("expected name");
    if (!Jsi_ValueIsFunction(interp, tocall))
        return Jsi_LogError("expected function");
    if (argc == 3) {
        nVal = Jsi_ValueArrayIndex(interp, args, 2);
        if (Jsi_GetIntFromValue(interp, nVal, &nArg) != JSI_OK)
            return JSI_ERROR;
    } else {
        Jsi_FunctionArguments(interp, tocall, &nArg);
    }
    if (nArg > SQLITE_LIMIT_FUNCTION_ARG)
        return Jsi_LogError("to many args");


    pFunc = dbFindSqlFunc(jdb, zName);
    if( pFunc==0 ) return JSI_ERROR;
    SQLSIGASSERT(pFunc,FUNC);

    pFunc->tocall = tocall;
    Jsi_IncrRefCount(interp, pFunc->tocall);
    rc = sqlite3_create_function(jdb->db, zName, nArg, SQLITE_UTF8,
                                 pFunc, jsiSqlFunc, 0, 0);

    if( rc!=SQLITE_OK ) {
        rc = JSI_ERROR;
        Jsi_LogError("function create error: %s", (char *)sqlite3_errmsg(jdb->db));
    }
    return JSI_OK;
}
