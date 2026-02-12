XMLTree::read_internal(bool validate)
{

	assert(!validate);

	delete _root;
	_root = 0;

	if (_doc) {
		xmlFreeDoc (_doc);
		_doc = 0;
	}


	xmlKeepBlanksDefault(0);


	xmlParserCtxtPtr ctxt = xmlNewParserCtxt();
	if (ctxt == NULL) {
		return false;
	}


	if (validate) {
		_doc = xmlCtxtReadFile(ctxt, _filename.c_str(), NULL, XML_PARSE_DTDVALID);
	} else {
		_doc = xmlCtxtReadFile(ctxt, _filename.c_str(), NULL, XML_PARSE_HUGE);
	}


	if (_doc == NULL) {
		xmlFreeParserCtxt(ctxt);
		return false;
	} else {

		if (validate && ctxt->valid == 0) {
			xmlFreeParserCtxt(ctxt);
			throw XMLException("Failed to validate document " + _filename);
		}
	}

	_root = readnode(xmlDocGetRootElement(_doc));


	xmlFreeParserCtxt(ctxt);

	return true;
}
