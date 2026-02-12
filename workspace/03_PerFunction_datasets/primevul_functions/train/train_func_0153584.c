storeRawNames(XML_Parser parser) {
  TAG *tag = parser->m_tagStack;
  while (tag) {
    int bufSize;
    int nameLen = sizeof(XML_Char) * (tag->name.strLen + 1);
    size_t rawNameLen;
    char *rawNameBuf = tag->buf + nameLen;


    if (tag->rawName == rawNameBuf)
      break;


    rawNameLen = ROUND_UP(tag->rawNameLength, sizeof(XML_Char));

    if (rawNameLen > (size_t)INT_MAX - nameLen)
      return XML_FALSE;
    bufSize = nameLen + (int)rawNameLen;
    if (bufSize > tag->bufEnd - tag->buf) {
      char *temp = (char *)REALLOC(parser, tag->buf, bufSize);
      if (temp == NULL)
        return XML_FALSE;


      if (tag->name.str == (XML_Char *)tag->buf)
        tag->name.str = (XML_Char *)temp;


      if (tag->name.localPart)
        tag->name.localPart
            = (XML_Char *)temp + (tag->name.localPart - (XML_Char *)tag->buf);
      tag->buf = temp;
      tag->bufEnd = temp + bufSize;
      rawNameBuf = temp + nameLen;
    }
    memcpy(rawNameBuf, tag->rawName, tag->rawNameLength);
    tag->rawName = rawNameBuf;
    tag = tag->parent;
  }
  return XML_TRUE;
}
