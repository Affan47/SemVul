bool PDFDoc::checkEncryption(const GooString *ownerPassword, const GooString *userPassword) {
  bool encrypted;
  bool ret;

  Object encrypt = xref->getTrailerDict()->dictLookup("Encrypt");
  if ((encrypted = encrypt.isDict())) {
    if ((secHdlr = SecurityHandler::make(this, &encrypt))) {
      if (secHdlr->isUnencrypted()) {

	ret = true;
      } else if (secHdlr->checkEncryption(ownerPassword, userPassword)) {

       	xref->setEncryption(secHdlr->getPermissionFlags(),
			    secHdlr->getOwnerPasswordOk(),
			    secHdlr->getFileKey(),
			    secHdlr->getFileKeyLength(),
			    secHdlr->getEncVersion(),
			    secHdlr->getEncRevision(),
			    secHdlr->getEncAlgorithm());
	ret = true;
      } else {

	ret = false;
      }
    } else {

      ret = false;
    }
  } else {

    ret = true;
  }
  return ret;
}
