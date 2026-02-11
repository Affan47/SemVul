writePageObjects(OutStream *outStr, XRef *xRef, Guint numOffset, GBool combine)
{
  Guint objectsCount = 0;
  Guchar *fileKey;
  CryptAlgorithm encAlgorithm;
  int keyLength;
  xRef->getEncryptionParameters(&fileKey, &encAlgorithm, &keyLength);

  for (int n = numOffset; n < xRef->getNumObjects(); n++) {
    if (xRef->getEntry(n)->type != xrefEntryFree) {
      Object obj;
      Ref ref;
      ref.num = n;
      ref.gen = xRef->getEntry(n)->gen;
      objectsCount++;
      getXRef()->fetch(ref.num - numOffset, ref.gen, &obj);
      Goffset offset = writeObjectHeader(&ref, outStr);
      if (combine) {
        writeObject(&obj, outStr, getXRef(), numOffset, NULL, cryptRC4, 0, 0, 0);
      } else if (xRef->getEntry(n)->getFlag(XRefEntry::Unencrypted)) {
        writeObject(&obj, outStr, NULL, cryptRC4, 0, 0, 0);
      } else {
        writeObject(&obj, outStr, fileKey, encAlgorithm, keyLength, ref.num, ref.gen);
      }
      writeObjectFooter(outStr);
      xRef->add(ref.num, ref.gen, offset, gTrue);
      obj.free();
    }
  }
  return objectsCount;
}
