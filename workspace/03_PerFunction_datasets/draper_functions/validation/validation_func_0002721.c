xmlC14NProcessNamespacesAxis(xmlC14NCtxPtr ctx, xmlNodePtr cur, int visible)
{
    xmlNodePtr n;
    xmlNsPtr ns, tmp;
    xmlListPtr list;
    int already_rendered;
    int has_empty_ns = 0;

    if ((ctx == NULL) || (cur == NULL) || (cur->type != XML_ELEMENT_NODE)) {
        xmlC14NErrParam("processing namespaces axis (c14n)");
        return (-1);
    }


    list = xmlListCreate(NULL, (xmlListDataCompare) xmlC14NNsCompare);
    if (list == NULL) {
        xmlC14NErrInternal("creating namespaces list (c14n)");
        return (-1);
    }


    for(n = cur; n != NULL; n = n->parent) {
        for(ns = n->nsDef; ns != NULL; ns = ns->next) {
            tmp = xmlSearchNs(cur->doc, cur, ns->prefix);

            if((tmp == ns) && !xmlC14NIsXmlNs(ns) && xmlC14NIsVisible(ctx, ns, cur)) {
                already_rendered = xmlC14NVisibleNsStackFind(ctx->ns_rendered, ns);
                if(visible) {
                    xmlC14NVisibleNsStackAdd(ctx->ns_rendered, ns, cur);
                }
                if(!already_rendered) {
                    xmlListInsert(list, ns);
                }
                if(xmlStrlen(ns->prefix) == 0) {
                    has_empty_ns = 1;
                }
            }
        }
    }


    if(visible && !has_empty_ns) {
        static xmlNs ns_default;

        memset(&ns_default, 0, sizeof(ns_default));
        if(!xmlC14NVisibleNsStackFind(ctx->ns_rendered, &ns_default)) {
            xmlC14NPrintNamespaces(&ns_default, ctx);
        }
    }


    xmlListWalk(list, (xmlListWalker) xmlC14NPrintNamespaces, (const void *) ctx);


    xmlListDelete(list);
    return (0);
}
