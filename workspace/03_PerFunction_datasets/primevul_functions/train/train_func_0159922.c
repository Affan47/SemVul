xmlXIncludeRecurseDoc(xmlXIncludeCtxtPtr ctxt, xmlDocPtr doc,
	              const xmlURL url ATTRIBUTE_UNUSED) {
    xmlXIncludeCtxtPtr newctxt;
    int i;


#ifdef DEBUG_XINCLUDE
    xmlGenericError(xmlGenericErrorContext, "Recursing in doc %s\n", doc->URL);
#endif


    newctxt = xmlXIncludeNewContext(doc);
    if (newctxt != NULL) {


	newctxt->_private = ctxt->_private;


	newctxt->incMax = ctxt->incMax;
	newctxt->incNr = ctxt->incNr;
        newctxt->incTab = (xmlXIncludeRefPtr *) xmlMalloc(newctxt->incMax *
		                          sizeof(newctxt->incTab[0]));
        if (newctxt->incTab == NULL) {
	    xmlXIncludeErrMemory(ctxt, (xmlNodePtr) doc, "processing doc");
	    xmlFree(newctxt);
	    return;
	}


	newctxt->urlMax = ctxt->urlMax;
	newctxt->urlNr = ctxt->urlNr;
	newctxt->urlTab = ctxt->urlTab;


	newctxt->base = xmlStrdup(ctxt->base);


	newctxt->incBase = ctxt->incNr;
	for (i = 0;i < ctxt->incNr;i++) {
	    newctxt->incTab[i] = ctxt->incTab[i];
	    newctxt->incTab[i]->count++;

	}


	newctxt->parseFlags = ctxt->parseFlags;
        newctxt->incTotal = ctxt->incTotal;
	xmlXIncludeDoProcess(newctxt, doc, xmlDocGetRootElement(doc), 0);
        ctxt->incTotal = newctxt->incTotal;
	for (i = 0;i < ctxt->incNr;i++) {
	    newctxt->incTab[i]->count--;
	    newctxt->incTab[i] = NULL;
	}


	ctxt->urlTab = newctxt->urlTab;
	ctxt->urlMax = newctxt->urlMax;

	newctxt->urlMax = 0;
	newctxt->urlNr = 0;
	newctxt->urlTab = NULL;

	xmlXIncludeFreeContext(newctxt);
    }
#ifdef DEBUG_XINCLUDE
    xmlGenericError(xmlGenericErrorContext, "Done recursing in doc %s\n", url);
#endif
}
