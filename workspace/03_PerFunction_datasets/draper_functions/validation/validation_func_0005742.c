xmlRelaxNGSchemaTypeHave(void *data ATTRIBUTE_UNUSED, const xmlChar * type)
{
    xmlSchemaTypePtr typ;

    if (type == NULL)
        return (-1);
    typ = xmlSchemaGetPredefinedType(type,
                                     BAD_CAST
                                     "http://www.w3.org/2001/XMLSchema");
    if (typ == NULL)
        return (0);
    return (1);
}
