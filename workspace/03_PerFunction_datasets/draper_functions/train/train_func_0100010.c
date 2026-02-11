DrawTextBase(PRectangle rc, Font &font_, int ybase, const char *s, int len, ColourAllocated fore)
{
  if (dc()) {
    PenColour(fore);
    _dc->setFont(font_.GetID());
    const int segmentLength = 1000;
    int xbase = rc.left;
    if (codecBuffer.length()) { codecBuffer=FXString::null; }
    if (!unicodeMode) {
      for (int p=0; p<len; p++) {
        if ((FXuchar)(s[p])>126) {
          codecBuffer.length(asciiCodec.mb2utflen(s,len));
          asciiCodec.mb2utf(&(codecBuffer.at(0)),codecBuffer.length(),s,len);
          len=codecBuffer.length();
          break;
        }
      }
    }
    while ((len > 0) && (xbase < maxCoordinate)) {
      int lenDraw = Platform::Minimum(len, segmentLength);
      _dc->drawText(xbase, ybase, codecBuffer.length()?codecBuffer.text():s, lenDraw);
      len -= lenDraw;
      if (len > 0) {
        xbase += font_.GetID()->getTextWidth(s, lenDraw);
      }
      s += lenDraw;
    }
  }
  if (codecBuffer.length()) { codecBuffer=FXString::null; }
}
