*/
void
xmlXPathTranslateFunction(xmlXPathParserContextPtr ctxt, int nargs) {
    xmlXPathObjectPtr str;
    xmlXPathObjectPtr from;
    xmlXPathObjectPtr to;
    xmlBufPtr target;
    int offset, max;
    xmlChar ch;
    const xmlChar *point;
    xmlChar *cptr;

    CHECK_ARITY(3);

    CAST_TO_STRING;
    to = valuePop(ctxt);
    CAST_TO_STRING;
    from = valuePop(ctxt);
    CAST_TO_STRING;
    str = valuePop(ctxt);

    target = xmlBufCreate();
    if (target) {
	max = xmlUTF8Strlen(to->stringval);
	for (cptr = str->stringval; (ch=*cptr); ) {
	    offset = xmlUTF8Strloc(from->stringval, cptr);
	    if (offset >= 0) {
		if (offset < max) {
		    point = xmlUTF8Strpos(to->stringval, offset);
		    if (point)
			xmlBufAdd(target, point, xmlUTF8Strsize(point, 1));
		}
	    } else
		xmlBufAdd(target, cptr, xmlUTF8Strsize(cptr, 1));


	    cptr++;
	    if ( ch & 0x80 ) {

		if ( (ch & 0xc0) != 0xc0 ) {
		    xmlGenericError(xmlGenericErrorContext,
			"xmlXPathTranslateFunction: Invalid UTF8 string\n");

		    break;
		}

		while ( (ch <<= 1) & 0x80 )
		    if ( (*cptr++ & 0xc0) != 0x80 ) {
			xmlGenericError(xmlGenericErrorContext,
			    "xmlXPathTranslateFunction: Invalid UTF8 string\n");

			break;
		    }
		if (ch & 0x80)
		    break;
	    }
	}
    }
    valuePush(ctxt, xmlXPathCacheNewString(ctxt->context,
	xmlBufContent(target)));
    xmlBufFree(target);
    xmlXPathReleaseObject(ctxt->context, str);
    xmlXPathReleaseObject(ctxt->context, from);
}
