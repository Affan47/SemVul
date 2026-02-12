xmlDOMWrapAdoptBranch(xmlDOMWrapCtxtPtr ctxt,
		      xmlDocPtr sourceDoc,
		      xmlNodePtr node,
		      xmlDocPtr destDoc,
		      xmlNodePtr destParent,
		      int options ATTRIBUTE_UNUSED)
{
    int ret = 0;
    xmlNodePtr cur, curElem = NULL;
    xmlNsMapPtr nsMap = NULL;
    xmlNsMapItemPtr mi;
    xmlNsPtr ns = NULL;
    int depth = -1, adoptStr = 1;

    int parnsdone;

    int ancestorsOnly = 0;


    if ((sourceDoc != NULL) &&
	(sourceDoc->dict == destDoc->dict))
	adoptStr = 0;
    else
	adoptStr = 1;


    if (ctxt)
	nsMap = (xmlNsMapPtr) ctxt->namespaceMap;


    if ((destParent == NULL) ||
	(ctxt && ctxt->getNsForNodeFunc))
    {
	parnsdone = 1;
    } else
	parnsdone = 0;

    cur = node;
    if ((cur != NULL) && (cur->type == XML_NAMESPACE_DECL))
	goto internal_error;

    while (cur != NULL) {


	if (cur->doc != sourceDoc) {


	    if (cur->next == NULL)
		goto leave_node;
	    do {
		cur = cur->next;
		if ((cur->type == XML_XINCLUDE_END) ||
		    (cur->doc == node->doc))
		    break;
	    } while (cur->next != NULL);

	    if (cur->doc != node->doc)
		goto leave_node;
	}
	cur->doc = destDoc;
	switch (cur->type) {
	    case XML_XINCLUDE_START:
	    case XML_XINCLUDE_END:


		return (-1);
	    case XML_ELEMENT_NODE:
		curElem = cur;
		depth++;


		if ((cur->nsDef) &&
		    ((ctxt == NULL) || (ctxt->getNsForNodeFunc == NULL)))
		{
		    if (! parnsdone) {


			if (xmlDOMWrapNSNormGatherInScopeNs(&nsMap,
			    destParent) == -1)
			    goto internal_error;
			parnsdone = 1;
		    }
		    for (ns = cur->nsDef; ns != NULL; ns = ns->next) {


			if (XML_NSMAP_NOTEMPTY(nsMap)) {
			    XML_NSMAP_FOREACH(nsMap, mi) {
				if ((mi->depth >= XML_TREE_NSMAP_PARENT) &&
				    (mi->shadowDepth == -1) &&
				    ((ns->prefix == mi->newNs->prefix) ||
				    xmlStrEqual(ns->prefix,
				    mi->newNs->prefix))) {

				    mi->shadowDepth = depth;
				}
			    }
			}


			if (xmlDOMWrapNsMapAddItem(&nsMap, -1,
			    ns, ns, depth) == NULL)
			    goto internal_error;
		    }
		}

	    case XML_ATTRIBUTE_NODE:

		if (cur->ns == NULL)
		    goto ns_end;

		if (! parnsdone) {
		    if (xmlDOMWrapNSNormGatherInScopeNs(&nsMap,
			destParent) == -1)
			goto internal_error;
		    parnsdone = 1;
		}


		if (XML_NSMAP_NOTEMPTY(nsMap)) {


		    XML_NSMAP_FOREACH(nsMap, mi) {
			if ((mi->shadowDepth == -1) &&
			    (cur->ns == mi->oldNs)) {

			    cur->ns = mi->newNs;
			    goto ns_end;
			}
		    }
		}


		if ((ctxt) && (ctxt->getNsForNodeFunc)) {


		    ns = ctxt->getNsForNodeFunc(ctxt, cur,
			cur->ns->href, cur->ns->prefix);


		    if (xmlDOMWrapNsMapAddItem(&nsMap, -1,
			    cur->ns, ns, XML_TREE_NSMAP_CUSTOM) == NULL)
			goto internal_error;
		    cur->ns = ns;
		} else {


		    if (xmlDOMWrapNSNormAquireNormalizedNs(destDoc,

			destParent ? curElem : NULL,
			cur->ns, &ns,
			&nsMap, depth,
			ancestorsOnly,

			(cur->type == XML_ATTRIBUTE_NODE) ? 1 : 0) == -1)
			goto internal_error;
		    cur->ns = ns;
		}
ns_end:


		XML_TREE_ADOPT_STR(cur->name)
		if (cur->type == XML_ELEMENT_NODE) {
		    cur->psvi = NULL;
		    cur->line = 0;
		    cur->extra = 0;


		    if (cur->properties != NULL) {


			cur = (xmlNodePtr) cur->properties;
			continue;
		    }
		} else {


		    if ((sourceDoc != NULL) &&
			(((xmlAttrPtr) cur)->atype == XML_ATTRIBUTE_ID))
		    {
			xmlRemoveID(sourceDoc, (xmlAttrPtr) cur);
		    }
		    ((xmlAttrPtr) cur)->atype = 0;
		    ((xmlAttrPtr) cur)->psvi = NULL;
		}
		break;
	    case XML_TEXT_NODE:
	    case XML_CDATA_SECTION_NODE:


		XML_TREE_ADOPT_STR_2(cur->content)
		goto leave_node;
	    case XML_ENTITY_REF_NODE:


		cur->content = NULL;
		cur->children = NULL;
		cur->last = NULL;
		if ((destDoc->intSubset) || (destDoc->extSubset)) {
		    xmlEntityPtr ent;


		    ent = xmlGetDocEntity(destDoc, cur->name);
		    if (ent != NULL) {
			cur->content = ent->content;
			cur->children = (xmlNodePtr) ent;
			cur->last = (xmlNodePtr) ent;
		    }
		}
		goto leave_node;
	    case XML_PI_NODE:
		XML_TREE_ADOPT_STR(cur->name)
		XML_TREE_ADOPT_STR_2(cur->content)
		break;
	    case XML_COMMENT_NODE:
		break;
	    default:
		goto internal_error;
	}


	if (cur->children != NULL) {
	    cur = cur->children;
	    continue;
	}

leave_node:
	if (cur == node)
	    break;
	if ((cur->type == XML_ELEMENT_NODE) ||
	    (cur->type == XML_XINCLUDE_START) ||
	    (cur->type == XML_XINCLUDE_END))
	{


	    if (XML_NSMAP_NOTEMPTY(nsMap)) {


		while ((nsMap->last != NULL) &&
		    (nsMap->last->depth >= depth))
		{
		    XML_NSMAP_POP(nsMap, mi)
		}


		XML_NSMAP_FOREACH(nsMap, mi) {
		    if (mi->shadowDepth >= depth)
			mi->shadowDepth = -1;
		}
	    }
	    depth--;
	}
	if (cur->next != NULL)
	    cur = cur->next;
	else if ((cur->type == XML_ATTRIBUTE_NODE) &&
	    (cur->parent->children != NULL))
	{
	    cur = cur->parent->children;
	} else {
	    cur = cur->parent;
	    goto leave_node;
	}
    }

    goto exit;

internal_error:
    ret = -1;

exit:


    if (nsMap != NULL) {
	if ((ctxt) && (ctxt->namespaceMap == nsMap)) {


	    if (nsMap->first) {
		if (nsMap->pool)
		    nsMap->last->next = nsMap->pool;
		nsMap->pool = nsMap->first;
		nsMap->first = NULL;
	    }
	} else
	    xmlDOMWrapNsMapFree(nsMap);
    }
    return(ret);
}
