xmlHTMLEncodeSend(void) {
    char *result;


    memset(&buffer[sizeof(buffer)-4], 0, 4);
    result = (char *) xmlEncodeEntitiesReentrant(NULL, BAD_CAST buffer);
    if (result) {
	xmlGenericError(xmlGenericErrorContext, "%s", result);
	xmlFree(result);
    }
    buffer[0] = 0;
}
