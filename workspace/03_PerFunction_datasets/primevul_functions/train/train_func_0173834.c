static Jsi_RC dbPrepareAndBind(
    Jsi_Db *jdb,
    char const *zIn,
    char const **pzOut,
    SqlPreparedStmt **ppPreStmt
) {
    if (dbPrepareStmt(jdb, zIn, pzOut, ppPreStmt) != JSI_OK)
        return JSI_ERROR;
    return dbBindStmt(jdb, *ppPreStmt);
}
