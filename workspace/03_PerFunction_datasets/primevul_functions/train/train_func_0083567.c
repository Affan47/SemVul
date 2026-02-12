xmlXIncludeDoProcess(xmlXIncludeCtxtPtr ctxt, xmlDocPtr doc, xmlNodePtr tree,
                     int skipRoot) {
    xmlNodePtr cur;
    int ret = 0;
    int i, start;

    if ((doc == NULL) || (tree == NULL) || (tree->type == XML_NAMESPACE_DECL))
	return(-1);
    if ((skipRoot) && (tree->children == NULL))
        return(-1);
    if (ctxt == NULL)
	return(-1);

    if (doc->URL != NULL) {
	ret = xmlXIncludeURLPush(ctxt, doc->URL);
	if (ret < 0)
	    return(-1);
    }
    start = ctxt->incNr;


    if (skipRoot)
        cur = tree->children;
    else
        cur = tree;
    do {

        if (xmlXIncludeTestNode(ctxt, cur) == 1) {
#ifdef FUZZING_BUILD_MODE_UNSAFE_FOR_PRODUCTION


            if (ctxt->incTotal >= 20)
                return(-1);
#endif
            ctxt->incTotal++;
            xmlXIncludePreProcessNode(ctxt, cur);
        } else if ((cur->children != NULL) &&
                   (cur->children->type != XML_ENTITY_DECL) &&
                   (cur->children->type != XML_XINCLUDE_START) &&
                   (cur->children->type != XML_XINCLUDE_END)) {
            cur = cur->children;
            continue;
        }
        do {
            if (cur == tree)
                break;
            if (cur->next != NULL) {
                cur = cur->next;
                break;
            }
            cur = cur->parent;
        } while (cur != NULL);
    } while ((cur != NULL) && (cur != tree));


    for (i = start;i < ctxt->incNr; i++) {
        xmlXIncludeLoadNode(ctxt, i);
	ret++;
    }


    for (i = ctxt->incBase;i < ctxt->incNr; i++) {
	if ((ctxt->incTab[i]->inc != NULL) ||
	    (ctxt->incTab[i]->emptyFb != 0))
	    xmlXIncludeIncludeNode(ctxt, i);
    }

    if (doc->URL != NULL)
	xmlXIncludeURLPop(ctxt);
    return(ret);
}
