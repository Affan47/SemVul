int PDFDoc::saveAs(OutStream *outStr, PDFWriteMode mode) {
  if (file && file->modificationTimeChangedSinceOpen())
    return errFileChangedSinceOpen;

  if (!xref->isModified() && mode == writeStandard) {

    saveWithoutChangesAs (outStr);
  } else if (mode == writeForceRewrite) {
    saveCompleteRewrite(outStr);
  } else {
    saveIncrementalUpdate(outStr);
  }

  return errNone;
}
