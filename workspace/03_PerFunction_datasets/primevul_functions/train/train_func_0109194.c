int FoFiTrueType::setupGSUB(const char *scriptName,
                            const char *languageName)
{
  Guint gsubTable;
  unsigned int i;
  Guint scriptList, featureList;
  Guint scriptCount;
  Guint tag;
  Guint scriptTable = 0;
  Guint langSys;
  Guint featureCount;
  Guint featureIndex;
  Guint ftable = 0;
  Guint llist;
  Guint scriptTag;
  int x;
  Guint pos;

  if (scriptName == 0) {
    gsubFeatureTable = 0;
    return 0;
  }
  scriptTag = charToTag(scriptName);

  if ((x = seekTable("GSUB")) < 0) {
    return 0;
  }
  gsubTable = tables[x].offset;
  pos = gsubTable+4;
  scriptList = getU16BE(pos,&parsedOk);
  pos += 2;
  featureList = getU16BE(pos,&parsedOk);
  pos += 2;
  llist = getU16BE(pos,&parsedOk);

  gsubLookupList = llist+gsubTable;

  pos = gsubTable+scriptList;
  scriptCount = getU16BE(pos,&parsedOk);
  pos += 2;

  for (i = 0;i < scriptCount;i++) {
    tag = getU32BE(pos,&parsedOk);
    pos += 4;
    scriptTable = getU16BE(pos,&parsedOk);
    pos += 2;
    if (tag == scriptTag) {

      break;
    }
  }
  if (i >= scriptCount) {

    return 0;
  }


  pos = gsubTable+scriptList+scriptTable;
  langSys = 0;
  if (languageName) {
    Guint langTag = charToTag(languageName);
    Guint langCount = getU16BE(pos+2,&parsedOk);
    for (i = 0;i < langCount && langSys == 0;i++) {
      tag = getU32BE(pos+4+i*(4+2),&parsedOk);
      if (tag == langTag) {
        langSys = getU16BE(pos+4+i*(4+2)+4,&parsedOk);
      }
    }
  }
  if (langSys == 0) {

    langSys = getU16BE(pos,&parsedOk);
  }


  if (langSys == 0) {

    return 0;
  }

  pos = gsubTable+scriptList+scriptTable+langSys+2;
  featureIndex = getU16BE(pos,&parsedOk);
  pos += 2;

  if (featureIndex != 0xffff) {
    Guint tpos;

    tpos = gsubTable+featureList;
    featureCount = getU16BE(tpos,&parsedOk);
    tpos = gsubTable+featureList+2+featureIndex*(4+2);
    tag = getU32BE(tpos,&parsedOk);
    tpos += 4;
    if (tag == vrt2Tag) {

      ftable = getU16BE(tpos,&parsedOk);

      gsubFeatureTable = ftable+gsubTable+featureList;
      return 0;
    } else if (tag == vertTag) {
      ftable = getU16BE(tpos,&parsedOk);
    }
  }
  featureCount = getU16BE(pos,&parsedOk);
  pos += 2;

  for (i = 0;i < featureCount;i++) {
    Guint oldPos;

    featureIndex = getU16BE(pos,&parsedOk);
    pos += 2;
    oldPos = pos;

    pos = gsubTable+featureList+2+featureIndex*(4+2);
    tag = getU32BE(pos,&parsedOk);
    pos += 4;
    if (tag == vrt2Tag) {

      ftable = getU16BE(pos,&parsedOk);
      break;
    } else if (ftable == 0 && tag == vertTag) {
      ftable = getU16BE(pos,&parsedOk);
    }
    pos = oldPos;
  }
  if (ftable == 0) {

    return 0;
  }

  gsubFeatureTable = ftable+gsubTable+featureList;
  return 0;
}
