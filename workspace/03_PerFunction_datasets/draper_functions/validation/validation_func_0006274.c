document_dispose (GObject *object)
{
  Document *doc = DOCUMENT(object);
  DocumentDetails *docdet;
  docdet = DOCUMENT_GET_PRIVATE(doc);

  if (docdet->short_filename) g_free(docdet->short_filename);
  if (docdet->file) g_object_unref(docdet->file);
  if (docdet->ico) g_object_unref(docdet->ico);
  if (docdet->contenttype) g_free(docdet->contenttype);

  G_OBJECT_CLASS (document_parent_class)->dispose (object);
}
