void PDFDoc::checkHeader() {
  char hdrBuf[headerSearchSize+1];
  char *p;
  char *tokptr;
  int i;
  int bytesRead;

  pdfMajorVersion = 0;
  pdfMinorVersion = 0;


  for (i = 0; i < headerSearchSize; ++i) {
    const int c = str->getChar();
    if (c == EOF)
      break;
    hdrBuf[i] = c;
  }
  bytesRead = i;
  hdrBuf[bytesRead] = '\0';


  bool headerFound = false;
  for (i = 0; i < bytesRead - 5; ++i) {
    if (!strncmp(&hdrBuf[i], "%PDF-", 5)) {
      headerFound = true;
      break;
    }
  }
  if (!headerFound) {
    error(errSyntaxWarning, -1, "May not be a PDF file (continuing anyway)");
    return;
  }
  str->moveStart(i);
  if (!(p = strtok_r(&hdrBuf[i+5], " \t\n\r", &tokptr))) {
    error(errSyntaxWarning, -1, "May not be a PDF file (continuing anyway)");
    return;
  }
  sscanf(p, "%d.%d", &pdfMajorVersion, &pdfMinorVersion);

}
