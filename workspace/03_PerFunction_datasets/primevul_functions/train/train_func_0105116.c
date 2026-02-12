Outline *PDFDoc::getOutline()
{
  if (!outline) {
    pdfdocLocker();

    outline = new Outline(catalog->getOutline(), xref);
  }

  return outline;
}
