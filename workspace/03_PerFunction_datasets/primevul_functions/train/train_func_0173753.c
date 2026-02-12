static Jsi_RC dbTransPostCmd(
    Jsi_Db *jdb,
    Jsi_Interp *interp,
    Jsi_RC result
) {
    static const char *azEnd[] = {
        "RELEASE _jsi_transaction",
        "COMMIT",
        "ROLLBACK TO _jsi_transaction ; RELEASE _jsi_transaction",
        "ROLLBACK"
    };
    Jsi_RC rc = result;
    const char *zEnd;

    jdb->nTransaction--;
    zEnd = azEnd[(rc==JSI_ERROR)*2 + (jdb->nTransaction==0)];

    jdb->disableAuth++;
    if( sqlite3_exec(jdb->db, zEnd, 0, 0, 0)) {


        if( rc!=JSI_ERROR ) {
            Jsi_LogError("%s", sqlite3_errmsg(jdb->db));
            rc = JSI_ERROR;
        }
        sqlite3_exec(jdb->db, "ROLLBACK", 0, 0, 0);
    }
    jdb->disableAuth--;

    return rc;
}
