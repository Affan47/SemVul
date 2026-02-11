CreateGingleSsrcElem(const buzz::QName& name, uint32 ssrc) {
  buzz::XmlElement* elem = new buzz::XmlElement(name, true);
  if (ssrc) {
    SetXmlBody(elem, ssrc);
  }
  return elem;
}
