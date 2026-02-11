doParsePdf(DataSource &source, int &reason)
{
  PdfFile loader;
  reason = -2;
  if (!loader.parse(source))
    return 0;

  reason = -3;
  const PdfObj *obj = loader.object(1);
  if (!obj || !obj->dict())
    return 0;
  const PdfObj *type = obj->dict()->get("Type", 0);
  if (!type || !type->name() || type->name()->value() != "Ipe")
    return 0;

  Buffer buffer = obj->dict()->stream();
  BufferSource xml(buffer);

  Document *self = new Document;
  if (obj->dict()->deflated()) {
    InflateSource xml1(xml);
    PdfStreamParser parser(loader, xml1);
    return doParse(self, parser, reason);
  } else {
    PdfStreamParser parser(loader, xml);
    return doParse(self, parser, reason);
  }
}
