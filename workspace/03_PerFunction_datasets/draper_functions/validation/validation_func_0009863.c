traverse()
{ if (updated)
    return SOAP_OK;
  if (vflag)
    cerr << "Analyzing definitions '" << (name?name:"") << "' in wsdl namespace '" << (targetNamespace?targetNamespace:"") << "'" << endl;
  updated = true;
  if (!targetNamespace)
  { if (vflag)
      cerr << "Warning: wsdl '" << (name?name:"") << "' has no targetNamespace" << endl;
    targetNamespace = soap_strdup(soap, "");
  }

  for (vector<wsdl__import>::iterator im = import.begin(); im != import.end(); ++im)
    (*im).traverse(*this);

  if (types)
    types->traverse(*this);

  for (vector<wsdl__message>::iterator mg = message.begin(); mg != message.end(); ++mg)
    (*mg).traverse(*this);

  for (vector<wsdl__portType>::iterator pt = portType.begin(); pt != portType.end(); ++pt)
    (*pt).traverse(*this);

  for (vector<wsdl__portType>::iterator in = interface_.begin(); in != interface_.end(); ++in)
    (*in).traverse(*this);

  for (vector<wsdl__binding>::iterator bg = binding.begin(); bg != binding.end(); ++bg)
    (*bg).traverse(*this);

  for (vector<wsdl__service>::iterator sv = service.begin(); sv != service.end(); ++sv)
    (*sv).traverse(*this);
  if (vflag)
    cerr << "End of definitions '" << (name?name:"") << "' namespace '" << (targetNamespace?targetNamespace:"") << "'" << endl;
  for (std::vector<wsp__Policy>::iterator p = wsp__Policy_.begin(); p != wsp__Policy_.end(); ++p)
    (*p).traverse(*this);
  return SOAP_OK;
}
