void PDFDoc::extractPDFSubtype() {
  pdfSubtype = subtypeNull;
  pdfPart = subtypePartNull;
  pdfConformance = subtypeConfNull;

  GooString *pdfSubtypeVersion = nullptr;

  if ((pdfSubtypeVersion = getDocInfoStringEntry("GTS_PDFA1Version"))) {
    pdfSubtype = subtypePDFA;
  } else if ((pdfSubtypeVersion = getDocInfoStringEntry("GTS_PDFEVersion"))) {
    pdfSubtype = subtypePDFE;
  } else if ((pdfSubtypeVersion = getDocInfoStringEntry("GTS_PDFUAVersion"))) {
    pdfSubtype = subtypePDFUA;
  } else if ((pdfSubtypeVersion = getDocInfoStringEntry("GTS_PDFVTVersion"))) {
    pdfSubtype = subtypePDFVT;
  } else if ((pdfSubtypeVersion = getDocInfoStringEntry("GTS_PDFXVersion"))) {
    pdfSubtype = subtypePDFX;
  } else {
    pdfSubtype = subtypeNone;
    pdfPart = subtypePartNone;
    pdfConformance = subtypeConfNone;
    return;
  }


  pdfPart = pdfPartFromString(pdfSubtype, pdfSubtypeVersion);


  pdfConformance = pdfConformanceFromString(pdfSubtypeVersion);

  delete pdfSubtypeVersion;
}
