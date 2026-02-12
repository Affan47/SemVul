_poppler_document_new_from_pdfdoc (PDFDoc  *newDoc,
                                   GError **error)
{
  PopplerDocument *document;

  if (!newDoc->isOk()) {
    int fopen_errno;
    switch (newDoc->getErrorCode())
      {
      case errOpenFile:


        fopen_errno = newDoc->getFopenErrno();
        g_set_error (error, G_FILE_ERROR,
		     g_file_error_from_errno (fopen_errno),
		     "%s", g_strerror (fopen_errno));
	break;
      case errBadCatalog:
        g_set_error (error, POPPLER_ERROR,
		     POPPLER_ERROR_BAD_CATALOG,
		     "Failed to read the document catalog");
	break;
      case errDamaged:
        g_set_error (error, POPPLER_ERROR,
		     POPPLER_ERROR_DAMAGED,
		     "PDF document is damaged");
	break;
      case errEncrypted:
        g_set_error (error, POPPLER_ERROR,
		     POPPLER_ERROR_ENCRYPTED,
		     "Document is encrypted");
	break;
      default:
        g_set_error (error, POPPLER_ERROR,
		     POPPLER_ERROR_INVALID,
		     "Failed to load document");
    }

    delete newDoc;
    return nullptr;
  }

  document = (PopplerDocument *) g_object_new (POPPLER_TYPE_DOCUMENT, nullptr);
  document->doc = newDoc;

  document->output_dev = new CairoOutputDev ();
  document->output_dev->startDoc(document->doc);

  return document;
}
