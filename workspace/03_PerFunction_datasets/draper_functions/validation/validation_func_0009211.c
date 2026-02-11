getPolygon(DOMElement *elem) {
  OGRPolygon *pg = new OGRPolygon();

  DOMElement *boundaryElem = (DOMElement *)elem->getFirstChild();
  while (boundaryElem != NULL) {
    char* pszTagName = XMLString::transcode(boundaryElem->getTagName());
    if (cmpStr(ILI2_BOUNDARY, pszTagName) == 0)
      pg->addRingDirectly(getBoundary(boundaryElem));
    XMLString::release(&pszTagName);
    boundaryElem = (DOMElement *)boundaryElem->getNextSibling();
  }

  return pg;
}
