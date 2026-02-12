xsltParseXSLTStylesheetElemCore(xsltCompilerCtxtPtr cctxt, xmlNodePtr node)
{
#ifdef WITH_XSLT_DEBUG_PARSING
    int templates = 0;
#endif
    xmlNodePtr cur, start = NULL;
    xsltStylesheetPtr style;

    if ((cctxt == NULL) || (node == NULL) ||
	(node->type != XML_ELEMENT_NODE))
	return(-1);

    style = cctxt->style;


    if (IS_XSLT_ELEM_FAST(node) && IS_XSLT_NAME(node, "include"))
    {
	xsltDocumentPtr include;


	include = ((xsltStyleItemIncludePtr) node->psvi)->include;
	if (include == NULL) {

	    return(-1);
	}


	node = xmlDocGetRootElement(include->doc);
	if (node == NULL) {
	    return(-1);
	}
    }

    if (node->children == NULL)
	return(0);


    xsltCompilerNodePush(cctxt, node);
    cctxt->inode->isRoot = 1;
    cctxt->inode->nsChanged = 0;


    cctxt->inode->litResElemInfo = cctxt->inodeList->litResElemInfo;


    cctxt->inode->inScopeNs =
	xsltCompilerBuildInScopeNsList(cctxt, node);


    if (xsltParseAttrXSLTVersion(cctxt, node,
	XSLT_ELEMENT_CATEGORY_XSLT) == 0)
    {


#ifdef XSLT_REFACTORED_MANDATORY_VERSION
	if (isXsltElem)
	    xsltTransformError(NULL, cctxt->style, node,
		"The attribute 'version' is missing.\n");
	cctxt->style->errors++;
#else

	xsltTransformError(NULL, cctxt->style, node,
	    "xsl:version is missing: document may not be a stylesheet\n");
	cctxt->style->warnings++;
#endif
    }


    cctxt->inode->extElemNs =
	xsltParseExtElemPrefixes(cctxt, node, NULL,
	    XSLT_ELEMENT_CATEGORY_XSLT);


    cctxt->inode->exclResultNs =
	xsltParseExclResultPrefixes(cctxt, node, NULL,
	    XSLT_ELEMENT_CATEGORY_XSLT);


    if (cctxt->inode->nsChanged)
	xsltLREInfoCreate(cctxt, node, 0);


    cur = node->children;
    while (cur != NULL) {
	if (cur->type == XML_TEXT_NODE) {
	    xsltTransformError(NULL, style, cur,
		"Misplaced text node (content: '%s').\n",
		(cur->content != NULL) ? cur->content : BAD_CAST "");
	    style->errors++;
	} else if (cur->type != XML_ELEMENT_NODE) {
	    xsltTransformError(NULL, style, cur, "Misplaced node.\n");
	    style->errors++;
	}
	cur = cur->next;
    }


    cur = node->children;
    while ((cur != NULL) && xsltParseFindTopLevelElem(cctxt, cur,
	    BAD_CAST "import", XSLT_NAMESPACE, 1, &cur) == 1)
	cur = cur->next;
    if (cur == NULL)
	goto exit;

    start = cur;


    while ((cur != NULL) &&
	xsltParseFindTopLevelElem(cctxt, cur,
	BAD_CAST "param", XSLT_NAMESPACE, 0, &cur) == 1)
    {
	xsltParseTopLevelXSLTElem(cctxt, cur, XSLT_FUNC_PARAM);
	cur = cur->next;
    }


    cur = start;
    while ((cur != NULL) &&
	xsltParseFindTopLevelElem(cctxt, cur,
	BAD_CAST "variable", XSLT_NAMESPACE, 0, &cur) == 1)
    {
	xsltParseTopLevelXSLTElem(cctxt, cur, XSLT_FUNC_VARIABLE);
	cur = cur->next;
    }


    cur = start;
    while (cur != NULL) {


	if (cur->type == XML_ELEMENT_NODE) {
	    if (cur->ns == NULL) {
		xsltTransformError(NULL, style, cur,
		    "Unexpected top-level element in no namespace.\n");
		style->errors++;
		cur = cur->next;
		continue;
	    }


	    if (IS_XSLT_ELEM_FAST(cur)) {


		if (IS_XSLT_NAME(cur, "import")) {
		    xsltTransformError(NULL, style, cur,
			"Misplaced xsl:import element.\n");
		    style->errors++;
		    cur = cur->next;
		    continue;
		}


		if (IS_XSLT_NAME(cur, "template")) {
#ifdef WITH_XSLT_DEBUG_PARSING
		    templates++;
#endif


		    xsltParseXSLTTemplate(cctxt, cur);
		} else if (IS_XSLT_NAME(cur, "variable")) {

		} else if (IS_XSLT_NAME(cur, "param")) {

		} else if (IS_XSLT_NAME(cur, "include")) {
		    if (cur->psvi != NULL)
			xsltParseXSLTStylesheetElemCore(cctxt, cur);
		    else {
			xsltTransformError(NULL, style, cur,
			    "Internal error: "
			    "(xsltParseXSLTStylesheetElemCore) "
			    "The xsl:include element was not compiled.\n");
			style->errors++;
		    }
		} else if (IS_XSLT_NAME(cur, "strip-space")) {

		    xsltParseStylesheetStripSpace(style, cur);
		} else if (IS_XSLT_NAME(cur, "preserve-space")) {

		    xsltParseStylesheetPreserveSpace(style, cur);
		} else if (IS_XSLT_NAME(cur, "output")) {

		    xsltParseStylesheetOutput(style, cur);
		} else if (IS_XSLT_NAME(cur, "key")) {

		    xsltParseStylesheetKey(style, cur);
		} else if (IS_XSLT_NAME(cur, "decimal-format")) {

		    xsltParseStylesheetDecimalFormat(style, cur);
		} else if (IS_XSLT_NAME(cur, "attribute-set")) {
		    xsltParseTopLevelXSLTElem(cctxt, cur,
			XSLT_FUNC_ATTRSET);
		} else if (IS_XSLT_NAME(cur, "namespace-alias")) {

		} else {
		    if (cctxt->inode->forwardsCompat) {


			xsltTransformError(NULL, style, cur,
			    "Forwards-compatible mode: Ignoring unknown XSLT "
			    "element '%s'.\n", cur->name);
			style->warnings++;
		    } else {
			xsltTransformError(NULL, style, cur,
			    "Unknown XSLT element '%s'.\n", cur->name);
			style->errors++;
		    }
		}
	    } else {
		xsltTopLevelFunction function;


		function = xsltExtModuleTopLevelLookup(cur->name,
		    cur->ns->href);
		if (function != NULL)
		    function(style, cur);
#ifdef WITH_XSLT_DEBUG_PARSING
		xsltGenericDebug(xsltGenericDebugContext,
		    "xsltParseXSLTStylesheetElemCore : User-defined "
		    "data element '%s'.\n", cur->name);
#endif
	    }
	}
	cur = cur->next;
    }

exit:

#ifdef WITH_XSLT_DEBUG_PARSING
    xsltGenericDebug(xsltGenericDebugContext,
	"### END of parsing top-level elements of doc '%s'.\n",
	node->doc->URL);
    xsltGenericDebug(xsltGenericDebugContext,
	"### Templates: %d\n", templates);
#ifdef XSLT_REFACTORED
    xsltGenericDebug(xsltGenericDebugContext,
	"### Max inodes: %d\n", cctxt->maxNodeInfos);
    xsltGenericDebug(xsltGenericDebugContext,
	"### Max LREs  : %d\n", cctxt->maxLREs);
#endif
#endif

    xsltCompilerNodePop(cctxt, node);
    return(0);
}
