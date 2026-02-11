xmlDOMWrapNSNormAddNsMapItem2(xmlNsPtr **list, int *size, int *number,
                        xmlNsPtr oldNs, xmlNsPtr newNs)
{
    if (*list == NULL) {
        *list = (xmlNsPtr *) xmlMalloc(6 * sizeof(xmlNsPtr));
        if (*list == NULL) {
            xmlTreeErrMemory("alloc ns map item");
            return(-1);
        }
        *size = 3;
        *number = 0;
    } else if ((*number) >= (*size)) {
        *size *= 2;
        *list = (xmlNsPtr *) xmlRealloc(*list,
            (*size) * 2 * sizeof(xmlNsPtr));
        if (*list == NULL) {
            xmlTreeErrMemory("realloc ns map item");
            return(-1);
        }
    }
    (*list)[2 * (*number)] = oldNs;
    (*list)[2 * (*number) +1] = newNs;
    (*number)++;
    return (0);
}
