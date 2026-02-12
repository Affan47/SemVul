parse_attr(struct ly_ctx *ctx, const char *data, unsigned int *len, struct lyxml_elem *parent)
{
    const char *c = data, *start, *delim;
    char *prefix = NULL, xml_flag, *str;
    int uc;
    struct lyxml_attr *attr = NULL, *a;
    unsigned int size;


    if (!strncmp(c, "xmlns", 5)) {

        attr = calloc(1, sizeof (struct lyxml_ns));
        LY_CHECK_ERR_RETURN(!attr, LOGMEM(ctx), NULL);

        attr->type = LYXML_ATTR_NS;
        ((struct lyxml_ns *)attr)->parent = parent;
        c += 5;
        if (*c != ':') {

            goto equal;
        }
        c++;
    } else {

        attr = calloc(1, sizeof *attr);
        LY_CHECK_ERR_RETURN(!attr, LOGMEM(ctx), NULL);

        attr->type = LYXML_ATTR_STD;
    }


    start = c;
    uc = lyxml_getutf8(ctx, c, &size);
    if (!is_xmlnamestartchar(uc)) {
        LOGVAL(ctx, LYE_XML_INVAL, LY_VLOG_NONE, NULL, "NameStartChar of the attribute");
        free(attr);
        return NULL;
    }
    xml_flag = 4;
    if (*c == 'x') {
        xml_flag = 1;
    }
    c += size;
    uc = lyxml_getutf8(ctx, c, &size);
    while (is_xmlnamechar(uc)) {
        if (attr->type == LYXML_ATTR_STD) {
            if ((*c == ':') && (xml_flag != 3)) {

                start = c + 1;


                if (prefix) {
                    LOGVAL(ctx, LYE_XML_INVAL, LY_VLOG_NONE, NULL, "prefix start, \":\" already parsed");
                    goto error;
                }
                prefix = malloc((c - data + 1) * sizeof *prefix);
                LY_CHECK_ERR_GOTO(!prefix, LOGMEM(ctx), error);
                memcpy(prefix, data, c - data);
                prefix[c - data] = '\0';
                attr->ns = lyxml_get_ns(parent, prefix);
                if (!attr->ns) {

                    attr->type = LYXML_ATTR_STD_UNRES;
                    attr->ns = (struct lyxml_ns *)prefix;
                    prefix = NULL;
                }
            } else if (((*c == 'm') && (xml_flag == 1)) ||
                    ((*c == 'l') && (xml_flag == 2))) {
                ++xml_flag;
            } else {
                xml_flag = 4;
            }
        }
        c += size;
        uc = lyxml_getutf8(ctx, c, &size);
    }


    size = c - start;
    attr->name = lydict_insert(ctx, start, size);

equal:

    ign_xmlws(c);
    if (*c != '=') {
        LOGVAL(ctx, LYE_XML_INVAL, LY_VLOG_NONE, NULL, "attribute definition, \"=\" expected");
        goto error;
    }
    c++;
    ign_xmlws(c);


    if (!*c || (*c != '"' && *c != '\'')) {
        LOGVAL(ctx, LYE_XML_INVAL, LY_VLOG_NONE, NULL, "attribute value, \" or \' expected");
        goto error;
    }
    delim = c;
    str = parse_text(ctx, ++c, *delim, &size);
    if (!str && !size) {
        goto error;
    }
    attr->value = lydict_insert_zc(ctx, str);

    *len = c + size + 1 - data;


    if (parent->attr) {

        for (a = parent->attr; a->next; a = a->next);

        a->next = attr;
    } else {

        parent->attr = attr;
    }

    free(prefix);
    return attr;

error:
    lyxml_free_attr(ctx, NULL, attr);
    free(prefix);
    return NULL;
}
