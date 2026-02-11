sftkdb_FindObjectsFinal(SFTKDBHandle *handle, SDBFind *find)
{
    SDB *db;
    if (handle == NULL) {
	return CKR_OK;
    }
    db = SFTK_GET_SDB(handle);
    return (*db->sdb_FindObjectsFinal)(db, find);
}
