static Jsi_RC dbEvalInit(
    Jsi_Interp *interp,
    DbEvalContext *p,
    Jsi_Db *jdb,
    const char* zSql,
    Jsi_DString *dStr,
    Jsi_Obj *pArray,
    Jsi_Obj *pValVar
) {
    p->dSql = dStr;
    p->zSql = Jsi_DSAppend(p->dSql, zSql?zSql:"", NULL);
    p->jdb = jdb;
    return JSI_OK;
}
