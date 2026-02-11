xmlSchemaPValAttrNode(xmlSchemaParserCtxtPtr ctxt,
                           xmlSchemaBasicItemPtr ownerItem,
                           xmlAttrPtr attr,
                           xmlSchemaTypePtr type,
                           const xmlChar **value)
{
    const xmlChar *val;

    if ((ctxt == NULL) || (type == NULL) || (attr == NULL))
        return (-1);

    val = xmlSchemaGetNodeContent(ctxt, (xmlNodePtr) attr);
    if (value != NULL)
        *value = val;

    return (xmlSchemaPValAttrNodeValue(ctxt, ownerItem, attr,
        val, type));
}
