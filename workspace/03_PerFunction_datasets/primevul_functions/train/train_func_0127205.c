static int areDoubleQuotedStringsEnabled(sqlite3 *db, NameContext *pTopNC){
  if( db->init.busy ) return 1;
  if( pTopNC->ncFlags & NC_IsDDL ){

    if( sqlite3WritableSchema(db) && (db->flags & SQLITE_DqsDML)!=0 ){
      return 1;
    }
    return (db->flags & SQLITE_DqsDDL)!=0;
  }else{

    return (db->flags & SQLITE_DqsDML)!=0;
  }
}
