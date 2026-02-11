EB_Xml_CompressDoc(xmlDocPtr doc, GWEN_BUFFER *buf) {
  xmlChar *xmlbuff;
  int buffersize;
  int rv;

  xmlDocDumpFormatMemory(doc, &xmlbuff, &buffersize, 1);
  if (buffersize==0) {
    DBG_ERROR(AQEBICS_LOGDOMAIN, "Empty doc");
    return -1;
  }

#if 0
  if (1) {
    FILE *f;

    f=fopen("/tmp/compress.txt", "w+");
    if (f) {
      fwrite((const char*)xmlbuff, buffersize, 1, f);
      fclose(f);
    }
    else {
      DBG_ERROR(0, "Could not create file");
      assert(0);
    }
  }
#endif

  rv=EB_Zip_Deflate((const char*)xmlbuff, buffersize, buf);
  xmlFree(xmlbuff);
  if (rv) {
    DBG_ERROR(AQEBICS_LOGDOMAIN, "Could not zip doc (%d)", rv);
    return -1;
  }

  return 0;
}
