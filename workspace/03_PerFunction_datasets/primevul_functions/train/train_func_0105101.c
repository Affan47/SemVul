void PDFDoc::saveCompleteRewrite (OutStream* outStr)
{


  xref->scanSpecialFlags();

  unsigned char *fileKey;
  CryptAlgorithm encAlgorithm;
  int keyLength;
  xref->getEncryptionParameters(&fileKey, &encAlgorithm, &keyLength);

  writeHeader(outStr, getPDFMajorVersion(), getPDFMinorVersion());
  XRef *uxref = new XRef();
  uxref->add(0, 65535, 0, false);
  xref->lock();
  for(int i=0; i<xref->getNumObjects(); i++) {
    Ref ref;
    XRefEntryType type = xref->getEntry(i)->type;
    if (type == xrefEntryFree) {
      ref.num = i;
      ref.gen = xref->getEntry(i)->gen;


      if (ref.gen > 0 && ref.num > 0)
        uxref->add(ref.num, ref.gen, 0, false);
    } else if (xref->getEntry(i)->getFlag(XRefEntry::DontRewrite)) {

      ref.num = i;
      ref.gen = xref->getEntry(i)->gen + 1;
      uxref->add(ref.num, ref.gen, 0, false);
    } else if (type == xrefEntryUncompressed){
      ref.num = i;
      ref.gen = xref->getEntry(i)->gen;
      Object obj1 = xref->fetch(ref, 1 );
      Goffset offset = writeObjectHeader(&ref, outStr);

      if (xref->getEntry(i)->getFlag(XRefEntry::Unencrypted)) {
        writeObject(&obj1, outStr, nullptr, cryptRC4, 0, 0, 0);
      } else {
        writeObject(&obj1, outStr, fileKey, encAlgorithm, keyLength, ref.num, ref.gen);
      }
      writeObjectFooter(outStr);
      uxref->add(ref.num, ref.gen, offset, true);
    } else if (type == xrefEntryCompressed) {
      ref.num = i;
      ref.gen = 0;
      Object obj1 = xref->fetch(ref, 1 );
      Goffset offset = writeObjectHeader(&ref, outStr);
      writeObject(&obj1, outStr, fileKey, encAlgorithm, keyLength, ref.num, ref.gen);
      writeObjectFooter(outStr);
      uxref->add(ref.num, ref.gen, offset, true);
    }
  }
  xref->unlock();
  Goffset uxrefOffset = outStr->getPos();
  writeXRefTableTrailer(uxrefOffset, uxref, true ,
                        uxref->getNumObjects(), outStr, false );
  delete uxref;
}
