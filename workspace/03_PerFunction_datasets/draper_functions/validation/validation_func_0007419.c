readXmlModules(xmlNodePtr n) {
  xmlNodePtr nn;
  const char *s;

  s=(const char*) xmlGetProp(n, BAD_CAST "keyfile");
  if (s && *s)
    m_keyFileName=std::string(s);

  nn=n->children;
  while(nn) {
    if (nn->type==XML_ELEMENT_NODE) {
      if (nn->name && strcasecmp((const char*)nn->name, "module")==0) {
	Module m(m_path.c_str());

	m.readXml(nn);
	m_modules.push_back(m);
      }
    }

    nn=nn->next;
  }
}
