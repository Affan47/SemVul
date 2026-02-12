xmlXIncludeCopyRange(xmlXIncludeCtxtPtr ctxt, xmlDocPtr target,
	                xmlDocPtr source, xmlXPathObjectPtr range) {

    xmlNodePtr list = NULL, last = NULL, listParent = NULL;
    xmlNodePtr tmp, tmp2;

    xmlNodePtr start, cur, end;
    int index1, index2;
    int level = 0, lastLevel = 0, endLevel = 0, endFlag = 0;

    if ((ctxt == NULL) || (target == NULL) || (source == NULL) ||
	(range == NULL))
	return(NULL);
    if (range->type != XPATH_RANGE)
	return(NULL);
    start = (xmlNodePtr) range->user;

    if ((start == NULL) || (start->type == XML_NAMESPACE_DECL))
	return(NULL);
    end = range->user2;
    if (end == NULL)
	return(xmlDocCopyNode(start, target, 1));
    if (end->type == XML_NAMESPACE_DECL)
        return(NULL);

    cur = start;
    index1 = range->index;
    index2 = range->index2;


    while (cur != NULL) {


	if (level < 0) {
	    while (level < 0) {

	        tmp2 = xmlDocCopyNode(listParent, target, 2);
	        xmlAddChild(tmp2, list);
	        list = tmp2;
	        listParent = listParent->parent;
	        level++;
	    }
	    last = list;
	    lastLevel = 0;
	}


	while (level < lastLevel) {
	    last = last->parent;
	    lastLevel --;
	}
	if (cur == end) {
	    if (cur->type == XML_TEXT_NODE) {
		const xmlChar *content = cur->content;
		int len;

		if (content == NULL) {
		    tmp = xmlNewTextLen(NULL, 0);
		} else {
		    len = index2;
		    if ((cur == start) && (index1 > 1)) {
			content += (index1 - 1);
			len -= (index1 - 1);
		    } else {
			len = index2;
		    }
		    tmp = xmlNewTextLen(content, len);
		}

		if (list == NULL)
		    return(tmp);

		if (level == lastLevel)
		    xmlAddNextSibling(last, tmp);
		else
		    xmlAddChild(last, tmp);
		return(list);
	    } else {
	        endLevel = level;
		endFlag = 1;

		tmp = xmlDocCopyNode(cur, target, 2);
		if (list == NULL) {
		    list = tmp;
		    listParent = cur->parent;
		} else {
		    if (level == lastLevel)
			xmlAddNextSibling(last, tmp);
		    else {
			xmlAddChild(last, tmp);
			lastLevel = level;
		    }
		}
		last = tmp;

		if (index2 > 1) {
		    end = xmlXIncludeGetNthChild(cur, index2 - 1);
		    index2 = 0;
		}
		if ((cur == start) && (index1 > 1)) {
		    cur = xmlXIncludeGetNthChild(cur, index1 - 1);
		    index1 = 0;
		}  else {
		    cur = cur->children;
		}
		level++;


		continue;
	    }
	} else if (cur == start) {
	    if ((cur->type == XML_TEXT_NODE) ||
		(cur->type == XML_CDATA_SECTION_NODE)) {
		const xmlChar *content = cur->content;

		if (content == NULL) {
		    tmp = xmlNewTextLen(NULL, 0);
		} else {
		    if (index1 > 1) {
			content += (index1 - 1);
			index1 = 0;
		    }
		    tmp = xmlNewText(content);
		}
		last = list = tmp;
		listParent = cur->parent;
	    } else {


		tmp = xmlDocCopyNode(cur, target, 2);
		list = last = tmp;
		listParent = cur->parent;
		if (index1 > 1) {
		    cur = xmlXIncludeGetNthChild(cur, index1 - 1);
		    level = lastLevel = 1;
		    index1 = 0;


		    continue;
		}
	    }
	} else {
	    tmp = NULL;
	    switch (cur->type) {
		case XML_DTD_NODE:
		case XML_ELEMENT_DECL:
		case XML_ATTRIBUTE_DECL:
		case XML_ENTITY_NODE:

		    break;
		case XML_ENTITY_DECL:

		    break;
		case XML_XINCLUDE_START:
		case XML_XINCLUDE_END:

		    break;
		case XML_ATTRIBUTE_NODE:

		    break;
		default:


		    tmp = xmlDocCopyNode(cur, target, 2);
		    break;
	    }
	    if (tmp != NULL) {
		if (level == lastLevel)
		    xmlAddNextSibling(last, tmp);
		else {
		    xmlAddChild(last, tmp);
		    lastLevel = level;
		}
		last = tmp;
	    }
	}


	cur = xmlXPtrAdvanceNode(cur, &level);
	if (endFlag && (level >= endLevel))
	    break;
    }
    return(list);
}
