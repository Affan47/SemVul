xmlExpStringDerive(xmlExpCtxtPtr ctxt, xmlExpNodePtr exp,
                   const xmlChar *str, int len) {
    const xmlChar *input;

    if ((exp == NULL) || (ctxt == NULL) || (str == NULL)) {
        return(NULL);
    }


    input = xmlDictExists(ctxt->dict, str, len);
    if (input == NULL) {
        return(forbiddenExp);
    }
    return(xmlExpStringDeriveInt(ctxt, exp, input));
}
