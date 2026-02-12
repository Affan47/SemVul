static Jsi_RC mdbEvalInit(
    Jsi_Interp *interp,
    MyDbEvalContext *p,
    MySqlObj *jdb,
    const char* zSql,
    Jsi_DString *dStr,
    Jsi_Obj *pArray,
    Jsi_Obj *pValVar
) {
    p->dzSql = dStr;
    p->zSql = Jsi_DSAppend(p->dzSql, zSql?zSql:"", NULL);
    p->jdb = jdb;
    return JSI_OK;
}
