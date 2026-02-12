void PDFDoc::setDocInfoStringEntry(const char *key, GooString *value)
{
  bool removeEntry = !value || value->getLength() == 0 || value->hasJustUnicodeMarker();
  if (removeEntry) {
    delete value;
  }

  Object infoObj = getDocInfo();
  if (infoObj.isNull() && removeEntry) {

    return;
  }

  infoObj = createDocInfoIfNoneExists();
  if (removeEntry) {
    infoObj.dictSet(key, Object(objNull));
  } else {
    infoObj.dictSet(key, Object(value));
  }


  if (infoObj.dictGetLength() == 0) {

    removeDocInfo();
  } else {
    setDocInfoModified(&infoObj);
  }
}
