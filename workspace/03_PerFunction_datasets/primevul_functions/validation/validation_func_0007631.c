static int zipfileRegister(sqlite3 *db){
  static sqlite3_module zipfileModule = {
    1,
    zipfileConnect,
    zipfileConnect,
    zipfileBestIndex,
    zipfileDisconnect,
    zipfileDisconnect,
    zipfileOpen,
    zipfileClose,
    zipfileFilter,
    zipfileNext,
    zipfileEof,
    zipfileColumn,
    0,
    zipfileUpdate,
    zipfileBegin,
    0,
    zipfileCommit,
    zipfileRollback,
    zipfileFindFunction,
    0,
  };

  int rc = sqlite3_create_module(db, "zipfile"  , &zipfileModule, 0);
  if( rc==SQLITE_OK ) rc = sqlite3_overload_function(db, "zipfile_cds", -1);
  if( rc==SQLITE_OK ){
    rc = sqlite3_create_function(db, "zipfile", -1, SQLITE_UTF8, 0, 0,
        zipfileStep, zipfileFinal
    );
  }
  return rc;
}
