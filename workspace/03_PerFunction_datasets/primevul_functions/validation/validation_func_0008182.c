xmlParseInternalSubset(xmlParserCtxtPtr ctxt) {


    if (RAW == '[') {
        int baseInputNr = ctxt->inputNr;
        ctxt->instate = XML_PARSER_DTD;
        NEXT;


	while (((RAW != ']') || (ctxt->inputNr > baseInputNr)) &&
               (ctxt->instate != XML_PARSER_EOF)) {
	    const xmlChar *check = CUR_PTR;
	    unsigned int cons = ctxt->input->consumed;

	    SKIP_BLANKS;
	    xmlParseMarkupDecl(ctxt);
	    xmlParsePEReference(ctxt);

	    if ((CUR_PTR == check) && (cons == ctxt->input->consumed)) {
		xmlFatalErr(ctxt, XML_ERR_INTERNAL_ERROR,
	     "xmlParseInternalSubset: error detected in Markup declaration\n");
                if (ctxt->inputNr > baseInputNr)
                    xmlPopInput(ctxt);
                else
		    break;
	    }
	}
	if (RAW == ']') {
	    NEXT;
	    SKIP_BLANKS;
	}
    }


    if (RAW != '>') {
	xmlFatalErr(ctxt, XML_ERR_DOCTYPE_NOT_FINISHED, NULL);
	return;
    }
    NEXT;
}
