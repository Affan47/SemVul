xsltNumberFormatGetMultipleLevel(xsltTransformContextPtr context,
				 xmlNodePtr node,
				 xsltCompMatchPtr countPat,
				 xsltCompMatchPtr fromPat,
				 double *array,
				 int max)
{
    int amount = 0;
    int cnt;
    xmlNodePtr oldCtxtNode;
    xmlNodePtr ancestor;
    xmlNodePtr preceding;
    xmlXPathParserContextPtr parser;

    oldCtxtNode = context->xpathCtxt->node;
    parser = xmlXPathNewParserContext(NULL, context->xpathCtxt);
    if (parser) {

	ancestor = node;
	while ((ancestor != NULL) && (ancestor->type != XML_DOCUMENT_NODE)) {
	    if ((fromPat != NULL) &&
		xsltTestCompMatchList(context, ancestor, fromPat))
		break;


	    if (xsltTestCompMatchCount(context, ancestor, countPat, node)) {

		cnt = 1;
                context->xpathCtxt->node = ancestor;
                preceding = xmlXPathNextPrecedingSibling(parser, ancestor);
                while (preceding != NULL) {
	            if (xsltTestCompMatchCount(context, preceding, countPat,
                                               node))
			cnt++;
                    context->xpathCtxt->node = ancestor;
                    preceding =
                        xmlXPathNextPrecedingSibling(parser, preceding);
		}
		array[amount++] = (double)cnt;
		if (amount >= max)
		    break;
	    }
            context->xpathCtxt->node = node;
            ancestor = xmlXPathNextAncestor(parser, ancestor);
	}
	xmlXPathFreeParserContext(parser);
    }
    context->xpathCtxt->node = oldCtxtNode;
    return amount;
}
