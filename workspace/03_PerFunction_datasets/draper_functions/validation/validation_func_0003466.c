xmlNewPattern(void) {
    xmlPatternPtr cur;

    cur = (xmlPatternPtr) xmlMalloc(sizeof(xmlPattern));
    if (cur == NULL) {
        ERROR(NULL, NULL, NULL,
                "xmlNewPattern : malloc failed\n");
        return(NULL);
    }
    memset(cur, 0, sizeof(xmlPattern));
    cur->maxStep = 10;
    cur->steps = (xmlStepOpPtr) xmlMalloc(cur->maxStep * sizeof(xmlStepOp));
    if (cur->steps == NULL) {
        xmlFree(cur);
        ERROR(NULL, NULL, NULL,
                "xmlNewPattern : malloc failed\n");
        return(NULL);
    }
    return(cur);
}
