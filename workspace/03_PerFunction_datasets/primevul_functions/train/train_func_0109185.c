int FoFiTrueType::checkGIDInCoverage(Guint coverage, Guint orgGID)
{
  int index = -1;
  Guint format;
  Guint count;
  Guint i;
  Guint pos;

  pos = coverage;
  format = getU16BE(pos,&parsedOk);
  pos += 2;
  switch (format) {
  case 1:
    count = getU16BE(pos,&parsedOk);
    pos += 2;


    for (i = 0;i < count;i++) {
      Guint gid;

      gid = getU16BE(pos,&parsedOk);
      pos += 2;
      if (gid == orgGID) {

        index = i;
        break;
      }
    }
    break;
  case 2:
    count = getU16BE(pos,&parsedOk);
    pos += 2;
    for (i = 0;i < count;i++) {
      Guint startGID, endGID;
      Guint startIndex;

      startGID = getU16BE(pos,&parsedOk);
      pos += 2;
      endGID = getU16BE(pos,&parsedOk);
      pos += 2;
      startIndex = getU16BE(pos,&parsedOk);
      pos += 2;


      if (startGID <= orgGID && orgGID <= endGID) {

        index = startIndex+orgGID-startGID;
        break;
      }
    }
    break;
  default:
    break;
  }
  return index;
}
