xsltParseStylesheetImportedDoc(xmlDocPtr doc,
			       xsltStylesheetPtr parentStyle) {
    xsltStylesheetPtr retStyle;

    if (doc == NULL)
	return(NULL);

    retStyle = xsltNewStylesheet();
    if (retStyle == NULL)
	return(NULL);


    retStyle->parent = parentStyle;


    if (doc->dict != NULL) {
        xmlDictFree(retStyle->dict);
	retStyle->dict = doc->dict;
#ifdef WITH_XSLT_DEBUG
        xsltGenericDebug(xsltGenericDebugContext,
	    "reusing dictionary from %s for stylesheet\n",
	    doc->URL);
#endif
	xmlDictReference(retStyle->dict);
    }


    xsltGatherNamespaces(retStyle);

#ifdef XSLT_REFACTORED
    {
	xsltCompilerCtxtPtr cctxt;
	xsltStylesheetPtr oldCurSheet;

	if (parentStyle == NULL) {
	    xsltPrincipalStylesheetDataPtr principalData;


	    retStyle->principal = retStyle;


	    principalData = xsltNewPrincipalStylesheetData();
	    if (principalData == NULL) {
		xsltFreeStylesheet(retStyle);
		return(NULL);
	    }
	    retStyle->principalData = principalData;


	    cctxt = xsltCompilationCtxtCreate(retStyle);
	    if (cctxt == NULL) {
		xsltFreeStylesheet(retStyle);
		return(NULL);
	    }
	    retStyle->compCtxt = (void *) cctxt;
	    cctxt->style = retStyle;
	    cctxt->dict = retStyle->dict;
	    cctxt->psData = principalData;


	    cctxt->depth = -1;
	    xsltCompilerNodePush(cctxt, (xmlNodePtr) doc);
	} else {


	    retStyle->principal = parentStyle->principal;
	    cctxt = parentStyle->compCtxt;
	    retStyle->compCtxt = cctxt;
	}


	oldCurSheet = cctxt->style;
	cctxt->style = retStyle;

	retStyle->doc = doc;
	xsltParseStylesheetProcess(retStyle, doc);

	cctxt->style = oldCurSheet;
	if (parentStyle == NULL) {


	    xsltCompilerNodePop(cctxt, (xmlNodePtr) doc);
	} else {


	}


	if (retStyle != NULL) {
	    if (retStyle->errors != 0) {
#ifdef XSLT_REFACTORED_XSLT_NSCOMP


		if (cctxt->psData->nsMap)
		    xsltRestoreDocumentNamespaces(cctxt->psData->nsMap, doc);
#endif


		retStyle->doc = NULL;


		if (parentStyle == NULL) {
		    xsltCleanupStylesheetTree(doc, xmlDocGetRootElement(doc));
		    if (retStyle->compCtxt != NULL) {
			xsltCompilationCtxtFree(retStyle->compCtxt);
			retStyle->compCtxt = NULL;
		    }
		}

		xsltFreeStylesheet(retStyle);
		retStyle = NULL;
	    }
	}
    }

#else


    retStyle->doc = doc;
    if (xsltParseStylesheetProcess(retStyle, doc) == NULL) {
		retStyle->doc = NULL;
		xsltFreeStylesheet(retStyle);
		retStyle = NULL;
    }
    if (retStyle != NULL) {
	if (retStyle->errors != 0) {
	    retStyle->doc = NULL;
	    if (parentStyle == NULL)
		xsltCleanupStylesheetTree(doc,
		    xmlDocGetRootElement(doc));
	    xsltFreeStylesheet(retStyle);
	    retStyle = NULL;
	}
    }
#endif

    return(retStyle);
}
