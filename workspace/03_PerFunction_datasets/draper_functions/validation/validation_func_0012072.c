xmlSchemaParseSchemaElement(xmlSchemaParserCtxtPtr ctxt,
                             xmlSchemaPtr schema,
                             xmlNodePtr node)
{
    xmlAttrPtr attr;
    const xmlChar *val;
    int res = 0, oldErrs = ctxt->nberrors;


    res = xmlSchemaPValAttrID(ctxt, node, BAD_CAST "id");
    HFAILURE;


    attr = xmlSchemaGetPropNode(node, "targetNamespace");
    if (attr != NULL) {
        res = xmlSchemaPValAttrNode(ctxt, NULL, attr,
            xmlSchemaGetBuiltInType(XML_SCHEMAS_ANYURI), NULL);
        HFAILURE;
        if (res != 0) {
            ctxt->stop = XML_SCHEMAP_S4S_ATTR_INVALID_VALUE;
            goto exit;
        }
    }
    attr = xmlSchemaGetPropNode(node, "elementFormDefault");
    if (attr != NULL) {
        val = xmlSchemaGetNodeContent(ctxt, (xmlNodePtr) attr);
        res = xmlSchemaPValAttrFormDefault(val, &schema->flags,
            XML_SCHEMAS_QUALIF_ELEM);
        HFAILURE;
        if (res != 0) {
            xmlSchemaPSimpleTypeErr(ctxt,
                XML_SCHEMAP_ELEMFORMDEFAULT_VALUE,
                NULL, (xmlNodePtr) attr, NULL,
                "(qualified | unqualified)", val, NULL, NULL, NULL);
        }
    }
    attr = xmlSchemaGetPropNode(node, "attributeFormDefault");
    if (attr != NULL) {
        val = xmlSchemaGetNodeContent(ctxt, (xmlNodePtr) attr);
        res = xmlSchemaPValAttrFormDefault(val, &schema->flags,
            XML_SCHEMAS_QUALIF_ATTR);
        HFAILURE;
        if (res != 0) {
            xmlSchemaPSimpleTypeErr(ctxt,
                XML_SCHEMAP_ATTRFORMDEFAULT_VALUE,
                NULL, (xmlNodePtr) attr, NULL,
                "(qualified | unqualified)", val, NULL, NULL, NULL);
        }
    }
    attr = xmlSchemaGetPropNode(node, "finalDefault");
    if (attr != NULL) {
        val = xmlSchemaGetNodeContent(ctxt, (xmlNodePtr) attr);
        res = xmlSchemaPValAttrBlockFinal(val, &(schema->flags), -1,
            XML_SCHEMAS_FINAL_DEFAULT_EXTENSION,
            XML_SCHEMAS_FINAL_DEFAULT_RESTRICTION,
            -1,
            XML_SCHEMAS_FINAL_DEFAULT_LIST,
            XML_SCHEMAS_FINAL_DEFAULT_UNION);
        HFAILURE;
        if (res != 0) {
            xmlSchemaPSimpleTypeErr(ctxt,
                XML_SCHEMAP_S4S_ATTR_INVALID_VALUE,
                NULL, (xmlNodePtr) attr, NULL,
                "(#all | List of (extension | restriction | list | union))",
                val, NULL, NULL, NULL);
        }
    }
    attr = xmlSchemaGetPropNode(node, "blockDefault");
    if (attr != NULL) {
        val = xmlSchemaGetNodeContent(ctxt, (xmlNodePtr) attr);
        res = xmlSchemaPValAttrBlockFinal(val, &(schema->flags), -1,
            XML_SCHEMAS_BLOCK_DEFAULT_EXTENSION,
            XML_SCHEMAS_BLOCK_DEFAULT_RESTRICTION,
            XML_SCHEMAS_BLOCK_DEFAULT_SUBSTITUTION, -1, -1);
        HFAILURE;
        if (res != 0) {
            xmlSchemaPSimpleTypeErr(ctxt,
                XML_SCHEMAP_S4S_ATTR_INVALID_VALUE,
                NULL, (xmlNodePtr) attr, NULL,
                "(#all | List of (extension | restriction | substitution))",
                val, NULL, NULL, NULL);
        }
    }

exit:
    if (oldErrs != ctxt->nberrors)
        res = ctxt->err;
    return(res);
exit_failure:
    return(-1);
}
