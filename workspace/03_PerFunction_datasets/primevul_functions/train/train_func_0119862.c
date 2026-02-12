xmlAddElementDecl(xmlValidCtxtPtr ctxt,
                  xmlDtdPtr dtd, const xmlChar *name,
                  xmlElementTypeVal type,
		  xmlElementContentPtr content) {
    xmlElementPtr ret;
    xmlElementTablePtr table;
    xmlAttributePtr oldAttributes = NULL;
    xmlChar *ns, *uqname;

    if (dtd == NULL) {
	return(NULL);
    }
    if (name == NULL) {
	return(NULL);
    }

    switch (type) {
        case XML_ELEMENT_TYPE_EMPTY:
	    if (content != NULL) {
		xmlErrValid(ctxt, XML_ERR_INTERNAL_ERROR,
		        "xmlAddElementDecl: content != NULL for EMPTY\n",
			NULL);
		return(NULL);
	    }
	    break;
	case XML_ELEMENT_TYPE_ANY:
	    if (content != NULL) {
		xmlErrValid(ctxt, XML_ERR_INTERNAL_ERROR,
		        "xmlAddElementDecl: content != NULL for ANY\n",
			NULL);
		return(NULL);
	    }
	    break;
	case XML_ELEMENT_TYPE_MIXED:
	    if (content == NULL) {
		xmlErrValid(ctxt, XML_ERR_INTERNAL_ERROR,
		        "xmlAddElementDecl: content == NULL for MIXED\n",
			NULL);
		return(NULL);
	    }
	    break;
	case XML_ELEMENT_TYPE_ELEMENT:
	    if (content == NULL) {
		xmlErrValid(ctxt, XML_ERR_INTERNAL_ERROR,
		        "xmlAddElementDecl: content == NULL for ELEMENT\n",
			NULL);
		return(NULL);
	    }
	    break;
	default:
	    xmlErrValid(ctxt, XML_ERR_INTERNAL_ERROR,
		    "Internal: ELEMENT decl corrupted invalid type\n",
		    NULL);
	    return(NULL);
    }


    uqname = xmlSplitQName2(name, &ns);
    if (uqname != NULL)
	name = uqname;


    table = (xmlElementTablePtr) dtd->elements;
    if (table == NULL) {
	xmlDictPtr dict = NULL;

	if (dtd->doc != NULL)
	    dict = dtd->doc->dict;
        table = xmlHashCreateDict(0, dict);
	dtd->elements = (void *) table;
    }
    if (table == NULL) {
	xmlVErrMemory(ctxt,
            "xmlAddElementDecl: Table creation failed!\n");
	if (uqname != NULL)
	    xmlFree(uqname);
	if (ns != NULL)
	    xmlFree(ns);
        return(NULL);
    }


    if ((dtd->doc != NULL) && (dtd->doc->intSubset != NULL)) {
	ret = xmlHashLookup2(dtd->doc->intSubset->elements, name, ns);
	if ((ret != NULL) && (ret->etype == XML_ELEMENT_TYPE_UNDEFINED)) {
	    oldAttributes = ret->attributes;
	    ret->attributes = NULL;
	    xmlHashRemoveEntry2(dtd->doc->intSubset->elements, name, ns, NULL);
	    xmlFreeElement(ret);
	}
    }


    ret = xmlHashLookup2(table, name, ns);
    if (ret != NULL) {
	if (ret->etype != XML_ELEMENT_TYPE_UNDEFINED) {
#ifdef LIBXML_VALID_ENABLED


	    xmlErrValidNode(ctxt, (xmlNodePtr) dtd, XML_DTD_ELEM_REDEFINED,
	                    "Redefinition of element %s\n",
			    name, NULL, NULL);
#endif
	    if (uqname != NULL)
		xmlFree(uqname);
            if (ns != NULL)
	        xmlFree(ns);
	    return(NULL);
	}
	if (ns != NULL) {
	    xmlFree(ns);
	    ns = NULL;
	}
    } else {
	ret = (xmlElementPtr) xmlMalloc(sizeof(xmlElement));
	if (ret == NULL) {
	    xmlVErrMemory(ctxt, "malloc failed");
	    if (uqname != NULL)
		xmlFree(uqname);
            if (ns != NULL)
	        xmlFree(ns);
	    return(NULL);
	}
	memset(ret, 0, sizeof(xmlElement));
	ret->type = XML_ELEMENT_DECL;


	ret->name = xmlStrdup(name);
	if (ret->name == NULL) {
	    xmlVErrMemory(ctxt, "malloc failed");
	    if (uqname != NULL)
		xmlFree(uqname);
            if (ns != NULL)
	        xmlFree(ns);
	    xmlFree(ret);
	    return(NULL);
	}
	ret->prefix = ns;


	if (xmlHashAddEntry2(table, name, ns, ret)) {
#ifdef LIBXML_VALID_ENABLED


	    xmlErrValidNode(ctxt, (xmlNodePtr) dtd, XML_DTD_ELEM_REDEFINED,
	                    "Redefinition of element %s\n",
			    name, NULL, NULL);
#endif
	    xmlFreeElement(ret);
	    if (uqname != NULL)
		xmlFree(uqname);
	    return(NULL);
	}


	ret->attributes = oldAttributes;
    }


    ret->etype = type;


    if ((ctxt != NULL) &&
        ((ctxt->finishDtd == XML_CTXT_FINISH_DTD_0) ||
         (ctxt->finishDtd == XML_CTXT_FINISH_DTD_1))) {
	ret->content = content;
	if (content != NULL)
	    content->parent = (xmlElementContentPtr) 1;
    } else {
	ret->content = xmlCopyDocElementContent(dtd->doc, content);
    }


    ret->parent = dtd;
    ret->doc = dtd->doc;
    if (dtd->last == NULL) {
	dtd->children = dtd->last = (xmlNodePtr) ret;
    } else {
        dtd->last->next = (xmlNodePtr) ret;
	ret->prev = dtd->last;
	dtd->last = (xmlNodePtr) ret;
    }
    if (uqname != NULL)
	xmlFree(uqname);
    return(ret);
}
