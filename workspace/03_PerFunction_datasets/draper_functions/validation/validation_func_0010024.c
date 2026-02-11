checkHeader() {
  char hdrBuf[headerSearchSize+1];
  char *p;
  char *tokptr;
  int i;

  pdfMajorVersion = 0;
  pdfMinorVersion = 0;
  for (i = 0; i < headerSearchSize; ++i) {
    hdrBuf[i] = str->getChar();
  }
  hdrBuf[headerSearchSize] = '\0';
  for (i = 0; i < headerSearchSize - 5; ++i) {
    if (!strncmp(&hdrBuf[i], "%PDF-", 5)) {
      break;
    }
  }
  if (i >= headerSearchSize - 5) {
    error(-1, "May not be a PDF file (continuing anyway)");
    return;
  }
  str->moveStart(i);
  if (!(p = strtok_r(&hdrBuf[i+5], " \t\n\r", &tokptr))) {
    error(-1, "May not be a PDF file (continuing anyway)");
    return;
  }
  sscanf(p, "%d.%d", &pdfMajorVersion, &pdfMinorVersion);

}
