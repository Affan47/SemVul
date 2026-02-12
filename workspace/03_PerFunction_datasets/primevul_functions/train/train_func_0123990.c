build_model(XML_Parser parser) {


  DTD *const dtd = parser->m_dtd;
  XML_Content *ret;
  XML_Char *str;


#if UINT_MAX >= SIZE_MAX
  if (dtd->scaffCount > (size_t)(-1) / sizeof(XML_Content)) {
    return NULL;
  }
  if (dtd->contentStringLen > (size_t)(-1) / sizeof(XML_Char)) {
    return NULL;
  }
#endif
  if (dtd->scaffCount * sizeof(XML_Content)
      > (size_t)(-1) - dtd->contentStringLen * sizeof(XML_Char)) {
    return NULL;
  }

  const size_t allocsize = (dtd->scaffCount * sizeof(XML_Content)
                            + (dtd->contentStringLen * sizeof(XML_Char)));

  ret = (XML_Content *)MALLOC(parser, allocsize);
  if (! ret)
    return NULL;


  XML_Content *dest = ret;
  XML_Content *const destLimit = &ret[dtd->scaffCount];
  XML_Content *const stackBottom = &ret[dtd->scaffCount];
  XML_Content *stackTop = stackBottom;
  str = (XML_Char *)&ret[dtd->scaffCount];


  (--stackTop)->numchildren = 0;

  for (; dest < destLimit; dest++) {

    const int src_node = (int)(stackTop++)->numchildren;


    dest->type = dtd->scaffold[src_node].type;
    dest->quant = dtd->scaffold[src_node].quant;
    if (dest->type == XML_CTYPE_NAME) {
      const XML_Char *src;
      dest->name = str;
      src = dtd->scaffold[src_node].name;
      for (;;) {
        *str++ = *src;
        if (! *src)
          break;
        src++;
      }
      dest->numchildren = 0;
      dest->children = NULL;
    } else {
      unsigned int i;
      int cn;
      dest->name = NULL;
      dest->numchildren = dtd->scaffold[src_node].childcnt;
      dest->children = &dest[1];


      stackTop -= dest->numchildren;
      for (i = 0, cn = dtd->scaffold[src_node].firstchild;
           i < dest->numchildren; i++, cn = dtd->scaffold[cn].nextsib) {
        (stackTop + i)->numchildren = (unsigned int)cn;
      }
    }
  }

  return ret;
}
