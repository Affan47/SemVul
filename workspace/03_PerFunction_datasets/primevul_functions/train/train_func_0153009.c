EXPORTED void xml_partial_response(struct transaction_t *txn,
                                   xmlDocPtr doc, xmlNodePtr node,
                                   unsigned level, xmlBufferPtr *buf)
{
    const char *eol = "\n";
    unsigned n;

    if (!config_httpprettytelemetry) {
        level = 0;
        eol = "";
    }


    if (!*buf) *buf = xmlBufferCreate();

    if (node) {

        for (n = 0; n < level * MARKUP_INDENT; n++) xmlBufferCCat(*buf, " ");


        xmlNodeDump(*buf, doc, node, level, config_httpprettytelemetry);


        xmlBufferCCat(*buf, eol);
    }
    else {

        xmlNodePtr root = xmlDocGetRootElement(doc);


        xmlBufferCCat(*buf, "</");
        if (root->ns->prefix) {
            xmlBufferCat(*buf, root->ns->prefix);
            xmlBufferCCat(*buf, ":");
        }
        xmlBufferCat(*buf, root->name);
        xmlBufferCCat(*buf, ">");


        xmlBufferCCat(*buf, eol);
    }

    if (txn) {

        write_body(0, txn,
                   (char *) xmlBufferContent(*buf), xmlBufferLength(*buf));


        xmlBufferEmpty(*buf);
    }
}
