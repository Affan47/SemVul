ajDomElementGetNthChildByTagNameC(AjPDomDocument doc,
                                                AjPDomElement element,
                                                const char *name,
                                                ajint n)
{
    AjPDomNodeList list;
    ajint len;
    AjPDomElement ret = NULL;

    list = ajDomElementGetElementsByTagNameC(element, name);

    if(!list)
        return NULL;

    len = ajDomNodeListGetLen(list);

    if(!len)
    {
        ajDomDocumentDestroyNodeList(doc, &list, AJDOMKEEP);
        return NULL;
    }

    if(n < 0 || n > len - 1)
    {
        ajDebug("ajDomElementgetNthChildByTagnameC: index out of range");
        ajDomDocumentDestroyNodeList(doc, &list, AJDOMKEEP);
        return NULL;
    }

    ret = ajDomNodeListItem(list, n);

    ajDomDocumentDestroyNodeList(doc, &list, AJDOMKEEP);

    return ret;
}
