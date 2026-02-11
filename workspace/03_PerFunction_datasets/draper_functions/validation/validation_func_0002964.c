getNextSerialNumber(sqlite3 *db)
{
    BIGNUM* one = BN_new();
    BN_one(one);

    sqlite3_stmt *stmt = NULL;

    char* sql = "SELECT SERIAL_NUMBER FROM CERT_META_DATA;";
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

    BIGNUM *num = NULL;
    if (SQLITE_OK == rc)
    {
        int res = sqlite3_step(stmt);
        if (res == SQLITE_ROW) {
            char *serial = (char*)sqlite3_column_text(stmt, 0);
            serialNumberStringToBigNum(serial, &num);
            BN_add(num, num, one);
            BN_free(one);
            sqlite3_finalize(stmt);

            return num;
        }
    }
    sqlite3_finalize(stmt);
    return one;
}
