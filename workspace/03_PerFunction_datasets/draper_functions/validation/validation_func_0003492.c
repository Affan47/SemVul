xmlSchemaPValAttr(xmlSchemaParserCtxtPtr ctxt,
                       xmlSchemaBasicItemPtr ownerItem,
                       xmlNodePtr ownerElem,
                       const char *name,
                       xmlSchemaTypePtr type,
                       const xmlChar **value)
{
    xmlAttrPtr attr;

    if ((ctxt == NULL) || (type == NULL)) {
        if (value != NULL)
            *value = NULL;
        return (-1);
    }
    if (type->type != XML_SCHEMA_TYPE_BASIC) {
        if (value != NULL)
            *value = NULL;
        xmlSchemaPErr(ctxt, ownerElem,
            XML_SCHEMAP_INTERNAL,
            "Internal error: xmlSchemaPValAttr, the given "
            "type '%s' is not a built-in type.\n",
            type->name, NULL);
        return (-1);
    }
    attr = xmlSchemaGetPropNode(ownerElem, name);
    if (attr == NULL) {
        if (value != NULL)
            *value = NULL;
        return (0);
    }
    return (xmlSchemaPValAttrNode(ctxt, ownerItem, attr,
        type, value));
}
