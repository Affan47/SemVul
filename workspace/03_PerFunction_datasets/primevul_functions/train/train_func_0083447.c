htmlAttrDumpOutput(xmlOutputBufferPtr buf, xmlDocPtr doc, xmlAttrPtr cur,
	           const char *encoding ATTRIBUTE_UNUSED) {
    xmlChar *value;


    if (cur == NULL) {
	return;
    }
    xmlOutputBufferWriteString(buf, " ");
    if ((cur->ns != NULL) && (cur->ns->prefix != NULL)) {
        xmlOutputBufferWriteString(buf, (const char *)cur->ns->prefix);
	xmlOutputBufferWriteString(buf, ":");
    }
    xmlOutputBufferWriteString(buf, (const char *)cur->name);
    if ((cur->children != NULL) && (!htmlIsBooleanAttr(cur->name))) {
	value = xmlNodeListGetString(doc, cur->children, 0);
	if (value) {
	    xmlOutputBufferWriteString(buf, "=");
	    if ((cur->ns == NULL) && (cur->parent != NULL) &&
		(cur->parent->ns == NULL) &&
		((!xmlStrcasecmp(cur->name, BAD_CAST "href")) ||
	         (!xmlStrcasecmp(cur->name, BAD_CAST "action")) ||
		 (!xmlStrcasecmp(cur->name, BAD_CAST "src")) ||
		 ((!xmlStrcasecmp(cur->name, BAD_CAST "name")) &&
		  (!xmlStrcasecmp(cur->parent->name, BAD_CAST "a"))))) {
		xmlChar *tmp = value;

		xmlBufCCat(buf->buffer, "\"");

		while (IS_BLANK_CH(*tmp)) tmp++;


		for ( ; ; ) {
		    xmlChar *escaped;
		    xmlChar endChar;
		    xmlChar *end = NULL;
		    xmlChar *start = (xmlChar *)xmlStrstr(tmp, BAD_CAST "<!--");
		    if (start != NULL) {
			end = (xmlChar *)xmlStrstr(tmp, BAD_CAST "-->");
			if (end != NULL) {
			    *start = '\0';
			}
		    }


		    escaped = xmlURIEscapeStr(tmp, BAD_CAST"@/:=?;#%&,+");
		    if (escaped != NULL) {
		        xmlBufCat(buf->buffer, escaped);
		        xmlFree(escaped);
		    } else {
		        xmlBufCat(buf->buffer, tmp);
		    }

		    if (end == NULL) {
			break;
		    }


		    *start = '<';
		    end += 3;
		    endChar = *end;
		    *end = '\0';
		    xmlBufCat(buf->buffer, start);
		    *end = endChar;
		    tmp = end;
		}

		xmlBufCCat(buf->buffer, "\"");
	    } else {
		xmlBufWriteQuotedString(buf->buffer, value);
	    }
	    xmlFree(value);
	} else  {
	    xmlOutputBufferWriteString(buf, "=\"\"");
	}
    }
}
