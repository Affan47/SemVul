xsltParseXSLTStylesheetElem(xsltCompilerCtxtPtr cctxt, xmlNodePtr node)
{
    xmlNodePtr cur, start;

    if ((cctxt == NULL) || (node == NULL))
	return(-1);

    if (node->children == NULL)
	goto exit;


    cur = node->children;


    while ((cur != NULL) &&
	xsltParseFindTopLevelElem(cctxt, cur,
	    BAD_CAST "import", XSLT_NAMESPACE, 1, &cur) == 1)
    {
	if (xsltParseStylesheetImport(cctxt->style, cur) != 0) {
	    cctxt->style->errors++;
	}
	cur = cur->next;
    }
    if (cur == NULL)
	goto exit;
    start = cur;


    cur = start;
    while ((cur != NULL) &&
	xsltParseFindTopLevelElem(cctxt, cur,
	    BAD_CAST "include", XSLT_NAMESPACE, 0, &cur) == 1)
    {
	xsltParseTopLevelXSLTElem(cctxt, cur, XSLT_FUNC_INCLUDE);
	cur = cur->next;
    }


    cur = start;
    while ((cur != NULL) &&
	xsltParseFindTopLevelElem(cctxt, cur,
	    BAD_CAST "namespace-alias", XSLT_NAMESPACE, 0, &cur) == 1)
    {
	xsltNamespaceAlias(cctxt->style, cur);
	cur = cur->next;
    }

    if (cctxt->isInclude) {


	goto exit;
    }


    xsltParseXSLTStylesheetElemCore(cctxt, node);
exit:

    return(0);
}
