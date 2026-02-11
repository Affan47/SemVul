tar_add_header(
  const char *zName,
  int nName,
  int iMode,
  unsigned int mTime,
  int iSize,
  char cType

){

  sqlite3_snprintf(8, (char*)&tball.aHdr[100], "%07o", iMode);
  sqlite3_snprintf(12, (char*)&tball.aHdr[136], "%011o", mTime);


  if( !is_iso646_name(zName, nName)
   || !tar_split_path(zName, nName, (char*)tball.aHdr, (char*)&tball.aHdr[345])
  ){
    int lastPage;

    approximate_split_path(zName, nName, (char*)tball.aHdr,
                           (char*)&tball.aHdr[345], 1);


    blob_reset(&tball.pax);
    add_pax_header("path", zName, nName);


    sqlite3_snprintf(12, (char*)&tball.aHdr[124], "%011o",
                     blob_size(&tball.pax));
    cksum_and_write_header('x');


    gzip_step(blob_buffer(&tball.pax), blob_size(&tball.pax));
    lastPage = blob_size(&tball.pax) % 512;
    if( lastPage!=0 ){
      gzip_step(tball.zSpaces, 512 - lastPage);
    }


    approximate_split_path(zName, nName, (char*)tball.aHdr,
                           (char*)&tball.aHdr[345], 0);
  }

  sqlite3_snprintf(12, (char*)&tball.aHdr[124], "%011o", iSize);


  cksum_and_write_header(cType);
}
