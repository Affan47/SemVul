xmlSecIOCallbackPtrListFind(xmlSecPtrListPtr list, const char* uri) {
    xmlSecIOCallbackPtr callbacks;
    xmlSecSize i, size;

    xmlSecAssert2(xmlSecPtrListCheckId(list, xmlSecIOCallbackPtrListId), NULL);
    xmlSecAssert2(uri != NULL, NULL);

    size = xmlSecPtrListGetSize(list);
    for(i = 0; i < size; ++i) {
        callbacks = (xmlSecIOCallbackPtr)xmlSecPtrListGetItem(list, i);
        xmlSecAssert2(callbacks != NULL, NULL);
        xmlSecAssert2(callbacks->matchcallback != NULL, NULL);

        if((callbacks->matchcallback(uri)) != 0) {
            return(callbacks);
        }
    }
    return(NULL);
}
