xmlValidateDocumentFinal(xmlValidCtxtPtr ctxt, xmlDocPtr doc) {
    xmlRefTablePtr table;
    unsigned int save;

    if (ctxt == NULL)
        return(0);
    if (doc == NULL) {
        xmlErrValid(ctxt, XML_DTD_NO_DOC,
		"xmlValidateDocumentFinal: doc == NULL\n", NULL);
	return(0);
    }


    save = ctxt->finishDtd;
    ctxt->finishDtd = 0;


    table = (xmlRefTablePtr) doc->refs;
    ctxt->doc = doc;
    ctxt->valid = 1;
    xmlHashScan(table, (xmlHashScanner) xmlValidateCheckRefCallback, ctxt);

    ctxt->finishDtd = save;
    return(ctxt->valid);
}
