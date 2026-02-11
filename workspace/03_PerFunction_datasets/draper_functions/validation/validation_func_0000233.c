parseBitmap()
{
  XmlAttributes att;
  if (!parseAttributes(att))
    return false;
  String objNumStr;
  if (att.slash() && att.has("pdfObject", objNumStr)) {
    int objNum = Lex(objNumStr).getInt();

    Bitmap bitmap(att, pdfStream(objNum));
    iBitmaps.push_back(bitmap);
  } else {
    String bits;
    if (!parsePCDATA("bitmap", bits))
      return false;
    Bitmap bitmap(att, bits);
    iBitmaps.push_back(bitmap);
  }
  return true;
}
