xsltParseSequenceConstructor(xsltCompilerCtxtPtr cctxt, xmlNodePtr cur)
{
    xsltStyleType type;
    xmlNodePtr deleteNode = NULL;

    if (cctxt == NULL) {
	xmlGenericError(xmlGenericErrorContext,
	    "xsltParseSequenceConstructor: Bad arguments\n");
	cctxt->style->errors++;
	return;
    }


    if (cctxt->inode->category == XSLT_ELEMENT_CATEGORY_EXTENSION) {
	cctxt->inode->extContentHandled = 1;
    }
    if (cur == NULL)
	return;


    while (cur != NULL) {
	if (deleteNode != NULL)	{
#ifdef WITH_XSLT_DEBUG_BLANKS
	    xsltGenericDebug(xsltGenericDebugContext,
	     "xsltParseSequenceConstructor: removing xsl:text element\n");
#endif
	    xmlUnlinkNode(deleteNode);
	    xmlFreeNode(deleteNode);
	    deleteNode = NULL;
	}
	if (cur->type == XML_ELEMENT_NODE) {

	    if (cur->psvi == xsltXSLTTextMarker) {


		xmlNodePtr tmp;

		cur->psvi = NULL;


		deleteNode = cur;


		tmp = cur->children;
		if (tmp) {


		    if ((tmp->type == XML_TEXT_NODE) ||
			(tmp->next == NULL))
		    {


			xmlUnlinkNode(tmp);
			xmlAddPrevSibling(cur, tmp);
		    } else {
			tmp = NULL;
			xsltTransformError(NULL, cctxt->style, cur,
			    "Element 'xsl:text': Invalid type "
			    "of node found in content.\n");
			cctxt->style->errors++;
		    }
		}
		if (cur->properties) {
		    xmlAttrPtr attr;


		    attr = cur->properties;
		    do {
			if ((attr->ns == NULL) &&
			    (attr->name != NULL) &&
			    (attr->name[0] == 'd') &&
			    xmlStrEqual(attr->name,
			    BAD_CAST "disable-output-escaping"))
			{


			    if ((attr->children != NULL) &&
				xmlStrEqual(attr->children->content,
				BAD_CAST "yes"))
			    {


				if (tmp)
				    tmp->name = xmlStringTextNoenc;
			    } else if ((attr->children == NULL) ||
				(attr->children->content == NULL) ||
				(!xmlStrEqual(attr->children->content,
				BAD_CAST "no")))
			    {
				xsltTransformError(NULL, cctxt->style,
				    cur,
				    "Attribute 'disable-output-escaping': "
				    "Invalid value. Expected is "
				    "'yes' or 'no'.\n");
				cctxt->style->errors++;
			    }
			    break;
			}
			attr = attr->next;
		    } while (attr != NULL);
		}
	    } else if (IS_XSLT_ELEM_FAST(cur)) {


		cur->psvi = NULL;
		type = xsltGetXSLTElementTypeByNode(cctxt, cur);
		switch (type) {
		    case XSLT_FUNC_APPLYIMPORTS:
		    case XSLT_FUNC_APPLYTEMPLATES:
		    case XSLT_FUNC_ATTRIBUTE:
		    case XSLT_FUNC_CALLTEMPLATE:
		    case XSLT_FUNC_CHOOSE:
		    case XSLT_FUNC_COMMENT:
		    case XSLT_FUNC_COPY:
		    case XSLT_FUNC_COPYOF:
		    case XSLT_FUNC_DOCUMENT:
		    case XSLT_FUNC_ELEMENT:
		    case XSLT_FUNC_FALLBACK:
		    case XSLT_FUNC_FOREACH:
		    case XSLT_FUNC_IF:
		    case XSLT_FUNC_MESSAGE:
		    case XSLT_FUNC_NUMBER:
		    case XSLT_FUNC_PI:
		    case XSLT_FUNC_TEXT:
		    case XSLT_FUNC_VALUEOF:
		    case XSLT_FUNC_VARIABLE:


			cctxt->inode->curChildType = type;
			xsltParseAnyXSLTElem(cctxt, cur);
			break;
		    default:
			xsltParseUnknownXSLTElem(cctxt, cur);
			cur = cur->next;
			continue;
		}
	    } else {


		xsltCompilerNodePush(cctxt, cur);


		if (cur->nsDef != NULL)
		    cctxt->inode->inScopeNs =
			xsltCompilerBuildInScopeNsList(cctxt, cur);


		if (cur->properties)
		    cctxt->inode->extElemNs =
			xsltParseExtElemPrefixes(cctxt,
			    cur, cctxt->inode->extElemNs,
			    XSLT_ELEMENT_CATEGORY_LRE);


		if ((cur->ns != NULL) &&
		    (cctxt->inode->extElemNs != NULL) &&
		    (xsltCheckExtPrefix(cctxt->style, cur->ns->href) == 1))
		{


		    cctxt->inode->category = XSLT_ELEMENT_CATEGORY_EXTENSION;
		    cctxt->inode->extContentHandled = 0;
		    if (cur->psvi != NULL) {
			cur->psvi = NULL;


			xsltTransformError(NULL, cctxt->style, cur,
			    "Internal error in xsltParseSequenceConstructor(): "
			    "Occupied PSVI field.\n");
			cctxt->style->errors++;
			cur = cur->next;
			continue;
		    }
		    cur->psvi = (void *)
			xsltPreComputeExtModuleElement(cctxt->style, cur);

		    if (cur->psvi == NULL) {


			cur->psvi = (void *) xsltExtMarker;
		    }


		    if ((cur->children != NULL) &&
			(cctxt->inode->extContentHandled == 0))
		    {


			xsltParseSequenceConstructor(cctxt, cur->children);
		    }
		} else {


		    cur->psvi = NULL;
		    cctxt->inode->category = XSLT_ELEMENT_CATEGORY_LRE;
		    if (cur->properties != NULL) {
			xmlAttrPtr attr = cur->properties;


			cctxt->inode->exclResultNs =
			    xsltParseExclResultPrefixes(cctxt, cur,
				cctxt->inode->exclResultNs,
				XSLT_ELEMENT_CATEGORY_LRE);


			xsltParseAttrXSLTVersion(cctxt, cur,
			    XSLT_ELEMENT_CATEGORY_LRE);


			do {
			    if ((attr->psvi != xsltXSLTAttrMarker) &&
				IS_XSLT_ATTR_FAST(attr))
			    {
				if (! xmlStrEqual(attr->name,
				    BAD_CAST "use-attribute-sets"))
				{
				    xsltTransformError(NULL, cctxt->style,
					cur,
					"Unknown XSLT attribute '%s'.\n",
					attr->name);
				    cctxt->style->errors++;
				} else {


				    attr->psvi = (void *) xsltXSLTAttrMarker;
				}
			    }
			    attr = attr->next;
			} while (attr != NULL);
		    }


		    if (cctxt->inode->nsChanged)
			xsltLREInfoCreate(cctxt, cur, 1);
		    cur->psvi = cctxt->inode->litResElemInfo;


		    if (cctxt->hasNsAliases)
			xsltLREBuildEffectiveNs(cctxt, cur);


		    if (cur->properties) {
			xmlAttrPtr attr = cur->properties;

			while (attr != NULL) {
			    xsltCompileAttr(cctxt->style, attr);
			    attr = attr->next;
			}
		    }


		    if (cur->children != NULL) {
			xsltParseSequenceConstructor(cctxt, cur->children);
		    }
		}


		xsltCompilerNodePop(cctxt, cur);
	    }
	}
	cur = cur->next;
    }
    if (deleteNode != NULL) {
#ifdef WITH_XSLT_DEBUG_BLANKS
	xsltGenericDebug(xsltGenericDebugContext,
	    "xsltParseSequenceConstructor: removing xsl:text element\n");
#endif
	xmlUnlinkNode(deleteNode);
	xmlFreeNode(deleteNode);
	deleteNode = NULL;
    }
}
