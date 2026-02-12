Object PDFDoc::createTrailerDict(int uxrefSize, bool incrUpdate, Goffset startxRef,
                                Ref *root, XRef *xRef, const char *fileName, Goffset fileSize)
{
  Dict *trailerDict = new Dict(xRef);
  trailerDict->set("Size", Object(uxrefSize));


  GooString message;
  char buffer[256];
  sprintf(buffer, "%i", (int)time(nullptr));
  message.append(buffer);

  if (fileName)
    message.append(fileName);

  sprintf(buffer, "%lli", (long long)fileSize);
  message.append(buffer);


  if (!xRef->getTrailerDict()->isNone()) {
    Object docInfo = xRef->getDocInfo();
    if (docInfo.isDict()) {
      for(int i=0; i<docInfo.getDict()->getLength(); i++) {
        Object obj2 = docInfo.getDict()->getVal(i);
        if (obj2.isString()) {
          message.append(obj2.getString());
        }
      }
    }
  }

  bool hasEncrypt = false;
  if (!xRef->getTrailerDict()->isNone()) {
    Object obj2 = xRef->getTrailerDict()->dictLookupNF("Encrypt");
    if (!obj2.isNull()) {
      trailerDict->set("Encrypt", std::move(obj2));
      hasEncrypt = true;
    }
  }


  unsigned char digest[16];
  md5((unsigned char*)message.c_str(), message.getLength(), digest);


  if (incrUpdate || hasEncrypt) {

    Object obj4  = xRef->getTrailerDict()->getDict()->lookup("ID");
    if (!obj4.isArray()) {
      error(errSyntaxWarning, -1, "PDFDoc::createTrailerDict original file's ID entry isn't an array. Trying to continue");
    } else {
      Array *array = new Array(xRef);

      array->add(obj4.arrayGet(0));
      array->add(Object(new GooString((const char*)digest, 16)));
      trailerDict->set("ID", Object(array));
    }
  } else {

    Array *array = new Array(xRef);
    array->add(Object(new GooString((const char*)digest, 16)));
    array->add(Object(new GooString((const char*)digest, 16)));
    trailerDict->set("ID", Object(array));
  }

  trailerDict->set("Root", Object(root->num, root->gen));

  if (incrUpdate) {
    trailerDict->set("Prev", Object(startxRef));
  }

  if (!xRef->getTrailerDict()->isNone()) {
    Object obj5 = xRef->getDocInfoNF();
    if (!obj5.isNull()) {
      trailerDict->set("Info", std::move(obj5));
    }
  }

  return Object(trailerDict);
}
