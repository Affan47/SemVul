AH_HHD14_Translate(const char *code, GWEN_BUFFER *cbuf) {
  GWEN_BUFFER *xbuf;
  int rv;

  xbuf=GWEN_Buffer_new(0, 256, 0, 1);
  AH_HHD14_CompressCode((const uint8_t*) code, xbuf);

  AH_HHD14_ExtractCode(xbuf);

  DBG_ERROR(AQHBCI_LOGDOMAIN, "HHD: Raw data is [%s]", GWEN_Buffer_GetStart(xbuf));

  rv=AH_HHD14__Translate(GWEN_Buffer_GetStart(xbuf), cbuf);
  if (rv<0) {
    DBG_INFO(AQHBCI_LOGDOMAIN, "here (%d)", rv);
    GWEN_Buffer_free(xbuf);
    return rv;
  }
  GWEN_Buffer_free(xbuf);
  return 0;
}
