xmlValidatePopElement(xmlValidCtxtPtr ctxt, xmlDocPtr doc ATTRIBUTE_UNUSED,
                      xmlNodePtr elem ATTRIBUTE_UNUSED,
		      const xmlChar *qname ATTRIBUTE_UNUSED) {
    int ret = 1;

    if (ctxt == NULL)
        return(0);

    if ((ctxt->vstateNr > 0) && (ctxt->vstate != NULL)) {
	xmlValidStatePtr state = ctxt->vstate;
	xmlElementPtr elemDecl;


	if (state->elemDecl != NULL) {
	    elemDecl = state->elemDecl;

	    if (elemDecl->etype == XML_ELEMENT_TYPE_ELEMENT) {
		if (state->exec != NULL) {
		    ret = xmlRegExecPushString(state->exec, NULL, NULL);
		    if (ret == 0) {
			xmlErrValidNode(ctxt, state->node,
			                XML_DTD_CONTENT_MODEL,
	   "Element %s content does not follow the DTD, Expecting more child\n",
			       state->node->name, NULL,NULL);
		    } else {


			ret = 1;
		    }
		}
	    }
	}
	vstateVPop(ctxt);
    }
    return(ret);
}
