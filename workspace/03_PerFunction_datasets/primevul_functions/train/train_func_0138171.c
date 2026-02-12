xsltParseUnknownXSLTElem(xsltCompilerCtxtPtr cctxt,
			    xmlNodePtr node)
{
    if ((cctxt == NULL) || (node == NULL))
	return(-1);


    if (cctxt->inode->category == XSLT_ELEMENT_CATEGORY_EXTENSION) {
	cctxt->inode->extContentHandled = 1;
    }
    if (cctxt->inode->forwardsCompat == 0) {


	xsltTransformError(NULL, cctxt->style, node,
	    "Unknown XSLT element '%s'.\n", node->name);
	cctxt->style->errors++;
	return(1);
    }


    if (cctxt->unknownItem == NULL) {


	cctxt->unknownItem = xsltForwardsCompatUnkownItemCreate(cctxt);
	if (cctxt->unknownItem == NULL) {
	    node->psvi = NULL;
	    return(-1);
	}
    }
    node->psvi = cctxt->unknownItem;
    if (node->children == NULL)
	return(0);
    else {
	xmlNodePtr child = node->children;

	xsltCompilerNodePush(cctxt, node);


	if (node->nsDef != NULL)
	    cctxt->inode->inScopeNs =
		xsltCompilerBuildInScopeNsList(cctxt, node);


	do {
	    if ((child->type == XML_ELEMENT_NODE) &&
		IS_XSLT_ELEM_FAST(child) &&
		IS_XSLT_NAME(child, "fallback"))
	    {
		cctxt->inode->curChildType = XSLT_FUNC_FALLBACK;
		xsltParseAnyXSLTElem(cctxt, child);
	    }
	    child = child->next;
	} while (child != NULL);

	xsltCompilerNodePop(cctxt, node);
    }
    return(0);
}
