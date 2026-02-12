void PDFDoc::writeString (const GooString* s, OutStream* outStr, const unsigned char *fileKey,
                          CryptAlgorithm encAlgorithm, int keyLength, int objNum, int objGen)
{

  GooString *sEnc = nullptr;
  if (fileKey) {
    EncryptStream *enc = new EncryptStream(new MemStream(s->c_str(), 0, s->getLength(), Object(objNull)),
                                           fileKey, encAlgorithm, keyLength, objNum, objGen);
    sEnc = new GooString();
    int c;
    enc->reset();
    while ((c = enc->getChar()) != EOF) {
      sEnc->append((char)c);
    }

    delete enc;
    s = sEnc;
  }


  if (s->hasUnicodeMarker()) {

    const char* c = s->c_str();
    outStr->printf("(");
    for(int i=0; i<s->getLength(); i++) {
      char unescaped = *(c+i)&0x000000ff;

      if (unescaped == '(' || unescaped == ')' || unescaped == '\\')
        outStr->printf("%c", '\\');
      outStr->printf("%c", unescaped);
    }
    outStr->printf(") ");
  } else {
    const char* c = s->c_str();
    outStr->printf("(");
    for(int i=0; i<s->getLength(); i++) {
      char unescaped = *(c+i)&0x000000ff;

      if (unescaped == '\r')
        outStr->printf("\\r");
      else if (unescaped == '\n')
        outStr->printf("\\n");
      else {
        if (unescaped == '(' || unescaped == ')' || unescaped == '\\') {
          outStr->printf("%c", '\\');
        }
        outStr->printf("%c", unescaped);
      }
    }
    outStr->printf(") ");
  }

  delete sEnc;
}
