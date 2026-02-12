xmlDOMWrapCloneNode(xmlDOMWrapCtxtPtr ctxt,
		      xmlDocPtr sourceDoc,
		      xmlNodePtr node,
		      xmlNodePtr *resNode,
		      xmlDocPtr destDoc,
		      xmlNodePtr destParent,
		      int deep,
		      int options ATTRIBUTE_UNUSED)
{
    int ret = 0;
    xmlNodePtr cur, curElem = NULL;
    xmlNsMapPtr nsMap = NULL;
    xmlNsMapItemPtr mi;
    xmlNsPtr ns;
    int depth = -1;


    int parnsdone = 0;


    int ancestorsOnly = 0;
    xmlNodePtr resultClone = NULL, clone = NULL, parentClone = NULL, prevClone = NULL;
    xmlNsPtr cloneNs = NULL, *cloneNsDefSlot = NULL;
    xmlDictPtr dict;

    if ((node == NULL) || (resNode == NULL) || (destDoc == NULL))
	return(-1);


    if (node->type != XML_ELEMENT_NODE)
	return(1);


    if ((node->doc != NULL) && (sourceDoc != NULL) &&
	(node->doc != sourceDoc)) {


	return (-1);
    }
    if (sourceDoc == NULL)
	sourceDoc = node->doc;
    if (sourceDoc == NULL)
        return (-1);

    dict = destDoc->dict;


    if (ctxt)
	nsMap = (xmlNsMapPtr) ctxt->namespaceMap;

    *resNode = NULL;

    cur = node;
    if ((cur != NULL) && (cur->type == XML_NAMESPACE_DECL))
        return(-1);

    while (cur != NULL) {
	if (cur->doc != sourceDoc) {


	    goto internal_error;
	}


	switch (cur->type) {
	    case XML_XINCLUDE_START:
	    case XML_XINCLUDE_END:


		goto internal_error;
		break;
	    case XML_ELEMENT_NODE:
	    case XML_TEXT_NODE:
	    case XML_CDATA_SECTION_NODE:
	    case XML_COMMENT_NODE:
	    case XML_PI_NODE:
	    case XML_DOCUMENT_FRAG_NODE:
	    case XML_ENTITY_REF_NODE:
	    case XML_ENTITY_NODE:


		clone = (xmlNodePtr) xmlMalloc(sizeof(xmlNode));
		if (clone == NULL) {
		    xmlTreeErrMemory("xmlDOMWrapCloneNode(): allocating a node");
		    goto internal_error;
		}
		memset(clone, 0, sizeof(xmlNode));


		if (resultClone != NULL) {
		    clone->parent = parentClone;
		    if (prevClone) {
			prevClone->next = clone;
			clone->prev = prevClone;
		    } else
			parentClone->children = clone;
		} else
		    resultClone = clone;

		break;
	    case XML_ATTRIBUTE_NODE:


		clone = (xmlNodePtr) xmlMalloc(sizeof(xmlAttr));
		if (clone == NULL) {
		    xmlTreeErrMemory("xmlDOMWrapCloneNode(): allocating an attr-node");
		    goto internal_error;
		}
		memset(clone, 0, sizeof(xmlAttr));


		if (resultClone != NULL) {
		    clone->parent = parentClone;
		    if (prevClone) {
			prevClone->next = clone;
			clone->prev = prevClone;
		    } else
			parentClone->properties = (xmlAttrPtr) clone;
		} else
		    resultClone = clone;
		break;
	    default:


		goto internal_error;
	}

	clone->type = cur->type;
	clone->doc = destDoc;


	if (cur->name == xmlStringText)
	    clone->name = xmlStringText;
	else if (cur->name == xmlStringTextNoenc)


	    clone->name = xmlStringTextNoenc;
	else if (cur->name == xmlStringComment)
	    clone->name = xmlStringComment;
	else if (cur->name != NULL) {
	    DICT_CONST_COPY(cur->name, clone->name);
	}

	switch (cur->type) {
	    case XML_XINCLUDE_START:
	    case XML_XINCLUDE_END:


		return (-1);
	    case XML_ELEMENT_NODE:
		curElem = cur;
		depth++;


		if (cur->nsDef != NULL) {
		    if (! parnsdone) {
			if (destParent && (ctxt == NULL)) {


			    if (xmlDOMWrapNSNormGatherInScopeNs(&nsMap,
				destParent) == -1)
				goto internal_error;
			}
			parnsdone = 1;
		    }


		    cloneNsDefSlot = &(clone->nsDef);
		    for (ns = cur->nsDef; ns != NULL; ns = ns->next) {


			cloneNs = (xmlNsPtr) xmlMalloc(sizeof(xmlNs));
			if (cloneNs == NULL) {
			    xmlTreeErrMemory("xmlDOMWrapCloneNode(): "
				"allocating namespace");
			    return(-1);
			}
			memset(cloneNs, 0, sizeof(xmlNs));
			cloneNs->type = XML_LOCAL_NAMESPACE;

			if (ns->href != NULL)
			    cloneNs->href = xmlStrdup(ns->href);
			if (ns->prefix != NULL)
			    cloneNs->prefix = xmlStrdup(ns->prefix);

			*cloneNsDefSlot = cloneNs;
			cloneNsDefSlot = &(cloneNs->next);


			if ((ctxt == NULL) ||
			    (ctxt->getNsForNodeFunc == NULL))
			{


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
				ns, cloneNs, depth) == NULL)
				goto internal_error;
			}
		    }
		}

		break;
	    case XML_ATTRIBUTE_NODE:


		break;
	    case XML_TEXT_NODE:
	    case XML_CDATA_SECTION_NODE:


		DICT_COPY(cur->content, clone->content);
		goto leave_node;
	    case XML_ENTITY_NODE:

		goto leave_node;
	    case XML_ENTITY_REF_NODE:
		if (sourceDoc != destDoc) {
		    if ((destDoc->intSubset) || (destDoc->extSubset)) {
			xmlEntityPtr ent;


			ent = xmlGetDocEntity(destDoc, cur->name);
			if (ent != NULL) {
			    clone->content = ent->content;
			    clone->children = (xmlNodePtr) ent;
			    clone->last = (xmlNodePtr) ent;
			}
		    }
		} else {


		    clone->content = cur->content;
		    clone->children = cur->children;
		    clone->last = cur->last;
		}
		goto leave_node;
	    case XML_PI_NODE:
		DICT_COPY(cur->content, clone->content);
		goto leave_node;
	    case XML_COMMENT_NODE:
		DICT_COPY(cur->content, clone->content);
		goto leave_node;
	    default:
		goto internal_error;
	}

	if (cur->ns == NULL)
	    goto end_ns_reference;


	if (! parnsdone) {
	    if (destParent && (ctxt == NULL)) {
		if (xmlDOMWrapNSNormGatherInScopeNs(&nsMap, destParent) == -1)
		    goto internal_error;
	    }
	    parnsdone = 1;
	}


	if (XML_NSMAP_NOTEMPTY(nsMap)) {


	    XML_NSMAP_FOREACH(nsMap, mi) {
		if ((mi->shadowDepth == -1) &&
		    (cur->ns == mi->oldNs)) {


		    clone->ns = mi->newNs;
		    goto end_ns_reference;
		}
	    }
	}


	if ((ctxt != NULL) && (ctxt->getNsForNodeFunc != NULL)) {


	    ns = ctxt->getNsForNodeFunc(ctxt, cur,
		cur->ns->href, cur->ns->prefix);


	    if (xmlDOMWrapNsMapAddItem(&nsMap, -1,
		cur->ns, ns, XML_TREE_NSMAP_CUSTOM) == NULL)
		goto internal_error;
	    clone->ns = ns;
	} else {


	    if (xmlDOMWrapNSNormAquireNormalizedNs(destDoc,

		destParent ? curElem : NULL,
		cur->ns, &ns,
		&nsMap, depth,

		ancestorsOnly,

		(cur->type == XML_ATTRIBUTE_NODE) ? 1 : 0) == -1)
		goto internal_error;
	    clone->ns = ns;
	}

end_ns_reference:


	if ((clone->type == XML_ATTRIBUTE_NODE) &&
	    (clone->parent != NULL))
	{
	    if (xmlIsID(destDoc, clone->parent, (xmlAttrPtr) clone)) {

		xmlChar *idVal;

		idVal = xmlNodeListGetString(cur->doc, cur->children, 1);
		if (idVal != NULL) {
		    if (xmlAddID(NULL, destDoc, idVal, (xmlAttrPtr) cur) == NULL) {

			xmlFree(idVal);
			goto internal_error;
		    }
		    xmlFree(idVal);
		}
	    }
	}


	if ((cur->type == XML_ELEMENT_NODE) && (cur->properties != NULL)) {
	    prevClone = NULL;
	    parentClone = clone;
	    cur = (xmlNodePtr) cur->properties;
	    continue;
	}
into_content:


	if (cur->children != NULL) {
	    if (deep || (cur->type == XML_ATTRIBUTE_NODE)) {
		prevClone = NULL;
		parentClone = clone;
		cur = cur->children;
		continue;
	    }
	}

leave_node:


	if (cur == node)
	    break;
	if ((cur->type == XML_ELEMENT_NODE) ||
	    (cur->type == XML_XINCLUDE_START) ||
	    (cur->type == XML_XINCLUDE_END)) {


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
	if (cur->next != NULL) {
	    prevClone = clone;
	    cur = cur->next;
	} else if (cur->type != XML_ATTRIBUTE_NODE) {


	    if (clone->parent != NULL)
		clone->parent->last = clone;
	    clone = clone->parent;
	    if (clone != NULL)
		parentClone = clone->parent;


	    cur = cur->parent;
	    goto leave_node;
	} else {

	    clone = clone->parent;
	    parentClone = clone->parent;


	    cur = cur->parent;
	    goto into_content;
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


    *resNode = resultClone;
    return (ret);
}
