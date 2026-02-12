Stream *Parser::makeStream(Object &&dict, Guchar *fileKey,
			   CryptAlgorithm encAlgorithm, int keyLength,
			   int objNum, int objGen, int recursion,
                           GBool strict) {
  BaseStream *baseStr;
  Stream *str;
  Goffset length;
  Goffset pos, endPos;


  lexer->skipToNextLine();
  if (!(str = lexer->getStream())) {
    return nullptr;
  }
  pos = str->getPos();


  Object obj = dict.dictLookup("Length", recursion);
  if (obj.isInt()) {
    length = obj.getInt();
  } else if (obj.isInt64()) {
    length = obj.getInt64();
  } else {
    error(errSyntaxError, getPos(), "Bad 'Length' attribute in stream");
    if (strict) return nullptr;
    length = 0;
  }


  if (xref && xref->getStreamEnd(pos, &endPos)) {
    length = endPos - pos;
  }


  if (!lexer->getStream()) {
    return nullptr;
  }
  baseStr = lexer->getStream()->getBaseStream();


  if (Lexer::LOOK_VALUE_NOT_CACHED != lexer->lookCharLastValueCached) {

      pos = pos - 1;
      lexer->lookCharLastValueCached = Lexer::LOOK_VALUE_NOT_CACHED;
  }
  if (unlikely(pos > LONG_LONG_MAX - length)) {
      return nullptr;
  }
  lexer->setPos(pos + length);


  shift();
  shift("endstream", objNum);
  if (buf1.isCmd("endstream")) {
    shift();
  } else {
    error(errSyntaxError, getPos(), "Missing 'endstream' or incorrect stream length");
    if (strict) return nullptr;
    if (xref && lexer->getStream()) {

      length = lexer->getPos() - pos;
      if (buf1.isCmd("endstream")) {
        dict.dictSet("Length", Object(length));
      }
    } else {


      length += 5000;
    }
  }


  str = baseStr->makeSubStream(pos, gTrue, length, std::move(dict));


  if (fileKey) {
    str = new DecryptStream(str, fileKey, encAlgorithm, keyLength,
			    objNum, objGen);
  }


  str = str->addFilters(str->getDict(), recursion);

  return str;
}
