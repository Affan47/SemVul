xmlValidateElementContent(xmlValidCtxtPtr ctxt, xmlNodePtr child,
       xmlElementPtr elemDecl, int warn, xmlNodePtr parent) {
    int ret = 1;
#ifndef  LIBXML_REGEXP_ENABLED
    xmlNodePtr repl = NULL, last = NULL, tmp;
#endif
    xmlNodePtr cur;
    xmlElementContentPtr cont;
    const xmlChar *name;

    if ((elemDecl == NULL) || (parent == NULL) || (ctxt == NULL))
	return(-1);
    cont = elemDecl->content;
    name = elemDecl->name;

#ifdef LIBXML_REGEXP_ENABLED

    if (elemDecl->contModel == NULL)
	ret = xmlValidBuildContentModel(ctxt, elemDecl);
    if (elemDecl->contModel == NULL) {
	return(-1);
    } else {
	xmlRegExecCtxtPtr exec;

	if (!xmlRegexpIsDeterminist(elemDecl->contModel)) {
	    return(-1);
	}
	ctxt->nodeMax = 0;
	ctxt->nodeNr = 0;
	ctxt->nodeTab = NULL;
	exec = xmlRegNewExecCtxt(elemDecl->contModel, NULL, NULL);
	if (exec != NULL) {
	    cur = child;
	    while (cur != NULL) {
		switch (cur->type) {
		    case XML_ENTITY_REF_NODE:


			if ((cur->children != NULL) &&
			    (cur->children->children != NULL)) {
			    nodeVPush(ctxt, cur);
			    cur = cur->children->children;
			    continue;
			}
			break;
		    case XML_TEXT_NODE:
			if (xmlIsBlankNode(cur))
			    break;
			ret = 0;
			goto fail;
		    case XML_CDATA_SECTION_NODE:

			ret = 0;
			goto fail;
		    case XML_ELEMENT_NODE:
			if ((cur->ns != NULL) && (cur->ns->prefix != NULL)) {
			    xmlChar fn[50];
			    xmlChar *fullname;

			    fullname = xmlBuildQName(cur->name,
				                     cur->ns->prefix, fn, 50);
			    if (fullname == NULL) {
				ret = -1;
				goto fail;
			    }
                            ret = xmlRegExecPushString(exec, fullname, NULL);
			    if ((fullname != fn) && (fullname != cur->name))
				xmlFree(fullname);
			} else {
			    ret = xmlRegExecPushString(exec, cur->name, NULL);
			}
			break;
		    default:
			break;
		}


		cur = cur->next;
		while (cur == NULL) {
		    cur = nodeVPop(ctxt);
		    if (cur == NULL)
			break;
		    cur = cur->next;
		}
	    }
	    ret = xmlRegExecPushString(exec, NULL, NULL);
fail:
	    xmlRegFreeExecCtxt(exec);
	}
    }
#else


    ctxt->vstateMax = 8;
    ctxt->vstateTab = (xmlValidState *) xmlMalloc(
		 ctxt->vstateMax * sizeof(ctxt->vstateTab[0]));
    if (ctxt->vstateTab == NULL) {
	xmlVErrMemory(ctxt, "malloc failed");
	return(-1);
    }


    ctxt->nodeMax = 0;
    ctxt->nodeNr = 0;
    ctxt->nodeTab = NULL;
    ctxt->vstate = &ctxt->vstateTab[0];
    ctxt->vstateNr = 1;
    CONT = cont;
    NODE = child;
    DEPTH = 0;
    OCCURS = 0;
    STATE = 0;
    ret = xmlValidateElementType(ctxt);
    if ((ret == -3) && (warn)) {
	xmlErrValidWarning(ctxt, child, XML_DTD_CONTENT_NOT_DETERMINIST,
	       "Content model for Element %s is ambiguous\n",
	                   name, NULL, NULL);
    } else if (ret == -2) {


	DEBUG_VALID_MSG("Found an entity reference, linearizing");
	cur = child;
	while (cur != NULL) {
	    switch (cur->type) {
		case XML_ENTITY_REF_NODE:


		    if ((cur->children != NULL) &&
			(cur->children->children != NULL)) {
			nodeVPush(ctxt, cur);
			cur = cur->children->children;
			continue;
		    }
		    break;
		case XML_TEXT_NODE:
		    if (xmlIsBlankNode(cur))
			break;

		case XML_CDATA_SECTION_NODE:

		case XML_ELEMENT_NODE:


		    tmp = (xmlNodePtr) xmlMalloc(sizeof(xmlNode));
		    if (tmp == NULL) {
			xmlVErrMemory(ctxt, "malloc failed");
			xmlFreeNodeList(repl);
			ret = -1;
			goto done;
		    }
		    tmp->type = cur->type;
		    tmp->name = cur->name;
		    tmp->ns = cur->ns;
		    tmp->next = NULL;
		    tmp->content = NULL;
		    if (repl == NULL)
			repl = last = tmp;
		    else {
			last->next = tmp;
			last = tmp;
		    }
		    if (cur->type == XML_CDATA_SECTION_NODE) {


			tmp->content = xmlStrdup(BAD_CAST "CDATA");
		    }
		    break;
		default:
		    break;
	    }


	    cur = cur->next;
	    while (cur == NULL) {
		cur = nodeVPop(ctxt);
		if (cur == NULL)
		    break;
		cur = cur->next;
	    }
	}


	ctxt->vstate = &ctxt->vstateTab[0];
	ctxt->vstateNr = 1;
	CONT = cont;
	NODE = repl;
	DEPTH = 0;
	OCCURS = 0;
	STATE = 0;
	ret = xmlValidateElementType(ctxt);
    }
#endif
    if ((warn) && ((ret != 1) && (ret != -3))) {
	if (ctxt != NULL) {
	    char expr[5000];
	    char list[5000];

	    expr[0] = 0;
	    xmlSnprintfElementContent(&expr[0], 5000, cont, 1);
	    list[0] = 0;
#ifndef LIBXML_REGEXP_ENABLED
	    if (repl != NULL)
		xmlSnprintfElements(&list[0], 5000, repl, 1);
	    else
#endif
		xmlSnprintfElements(&list[0], 5000, child, 1);

	    if (name != NULL) {
		xmlErrValidNode(ctxt, parent, XML_DTD_CONTENT_MODEL,
	   "Element %s content does not follow the DTD, expecting %s, got %s\n",
		       name, BAD_CAST expr, BAD_CAST list);
	    } else {
		xmlErrValidNode(ctxt, parent, XML_DTD_CONTENT_MODEL,
	   "Element content does not follow the DTD, expecting %s, got %s\n",
		       BAD_CAST expr, BAD_CAST list, NULL);
	    }
	} else {
	    if (name != NULL) {
		xmlErrValidNode(ctxt, parent, XML_DTD_CONTENT_MODEL,
		       "Element %s content does not follow the DTD\n",
		       name, NULL, NULL);
	    } else {
		xmlErrValidNode(ctxt, parent, XML_DTD_CONTENT_MODEL,
		       "Element content does not follow the DTD\n",
		                NULL, NULL, NULL);
	    }
	}
	ret = 0;
    }
    if (ret == -3)
	ret = 1;

#ifndef  LIBXML_REGEXP_ENABLED
done:


    while (repl != NULL) {
	tmp = repl->next;
	xmlFree(repl);
	repl = tmp;
    }
    ctxt->vstateMax = 0;
    if (ctxt->vstateTab != NULL) {
	xmlFree(ctxt->vstateTab);
	ctxt->vstateTab = NULL;
    }
#endif
    ctxt->nodeMax = 0;
    ctxt->nodeNr = 0;
    if (ctxt->nodeTab != NULL) {
	xmlFree(ctxt->nodeTab);
	ctxt->nodeTab = NULL;
    }
    return(ret);

}
