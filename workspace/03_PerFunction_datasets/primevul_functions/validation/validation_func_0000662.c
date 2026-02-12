lyxml_parse_elem(struct ly_ctx *ctx, const char *data, unsigned int *len, struct lyxml_elem *parent, int options)
{
    const char *c = data, *start, *e;
    const char *lws;
    int uc;
    char *str;
    char *prefix = NULL;
    unsigned int prefix_len = 0;
    struct lyxml_elem *elem = NULL, *child;
    struct lyxml_attr *attr;
    unsigned int size;
    int nons_flag = 0, closed_flag = 0;

    *len = 0;

    if (*c != '<') {
        return NULL;
    }


    c++;
    e = c;

    uc = lyxml_getutf8(ctx, e, &size);
    if (!is_xmlnamestartchar(uc)) {
        LOGVAL(ctx, LYE_XML_INVAL, LY_VLOG_NONE, NULL, "NameStartChar of the element");
        return NULL;
    }
    e += size;
    uc = lyxml_getutf8(ctx, e, &size);
    while (is_xmlnamechar(uc)) {
        if (*e == ':') {
            if (prefix_len) {
                LOGVAL(ctx, LYE_XML_INVAL, LY_VLOG_NONE, NULL, "element name, multiple colons found");
                goto error;
            }

            start = e + 1;


            prefix_len = e - c;
            LY_CHECK_ERR_GOTO(prefix, LOGVAL(ctx, LYE_XML_INCHAR, LY_VLOG_NONE, NULL, e), error);
            prefix = malloc((prefix_len + 1) * sizeof *prefix);
            LY_CHECK_ERR_GOTO(!prefix, LOGMEM(ctx), error);
            memcpy(prefix, c, prefix_len);
            prefix[prefix_len] = '\0';
            c = start;
        }
        e += size;
        uc = lyxml_getutf8(ctx, e, &size);
    }
    if (!*e) {
        LOGVAL(ctx, LYE_EOF, LY_VLOG_NONE, NULL);
        free(prefix);
        return NULL;
    }


    elem = calloc(1, sizeof *elem);
    LY_CHECK_ERR_RETURN(!elem, free(prefix); LOGMEM(ctx), NULL);

    elem->next = NULL;
    elem->prev = elem;
    if (parent) {
        lyxml_add_child(ctx, parent, elem);
    }


    elem->name = lydict_insert(ctx, c, e - c);
    c = e;

process:
    ign_xmlws(c);
    if (!strncmp("/>", c, 2)) {

        c += 2;
        elem->content = lydict_insert(ctx, "", 0);
        closed_flag = 1;
    } else if (*c == '>') {

        c++;
        lws = NULL;

        while (*c) {
            if (!strncmp(c, "</", 2)) {
                if (lws && !elem->child) {

                    goto store_content;
                }


                c += 2;

                e = c;
                uc = lyxml_getutf8(ctx, e, &size);
                if (!is_xmlnamestartchar(uc)) {
                    LOGVAL(ctx, LYE_XML_INVAL, LY_VLOG_XML, elem, "NameStartChar of the element");
                    goto error;
                }
                e += size;
                uc = lyxml_getutf8(ctx, e, &size);
                while (is_xmlnamechar(uc)) {
                    if (*e == ':') {

                        start = e + 1;


                        if (!prefix || memcmp(prefix, c, e - c)) {
                            LOGVAL(ctx, LYE_SPEC, LY_VLOG_XML, elem,
                                   "Invalid (different namespaces) opening (%s) and closing element tags.", elem->name);
                            goto error;
                        }
                        c = start;
                    }
                    e += size;
                    uc = lyxml_getutf8(ctx, e, &size);
                }
                if (!*e) {
                    LOGVAL(ctx, LYE_EOF, LY_VLOG_NONE, NULL);
                    goto error;
                }


                size = e - c;
                str = malloc((size + 1) * sizeof *str);
                LY_CHECK_ERR_GOTO(!str, LOGMEM(ctx), error);
                memcpy(str, c, e - c);
                str[e - c] = '\0';
                if (size != strlen(elem->name) || memcmp(str, elem->name, size)) {
                    LOGVAL(ctx, LYE_SPEC, LY_VLOG_XML, elem,
                           "Invalid (mixed names) opening (%s) and closing (%s) element tags.", elem->name, str);
                    free(str);
                    goto error;
                }
                free(str);
                c = e;

                ign_xmlws(c);
                if (*c != '>') {
                    LOGVAL(ctx, LYE_SPEC, LY_VLOG_XML, elem, "Data after closing element tag \"%s\".", elem->name);
                    goto error;
                }
                c++;
                if (!(elem->flags & LYXML_ELEM_MIXED) && !elem->content) {

                    elem->content = lydict_insert(ctx, "", 0);
                }
                closed_flag = 1;
                break;

            } else if (!strncmp(c, "<?", 2)) {
                if (lws) {

                    lws = NULL;
                }

                c += 2;
                if (parse_ignore(ctx, c, "?>", &size)) {
                    goto error;
                }
                c += size;
            } else if (!strncmp(c, "<!--", 4)) {
                if (lws) {

                    lws = NULL;
                }

                c += 4;
                if (parse_ignore(ctx, c, "-->", &size)) {
                    goto error;
                }
                c += size;
            } else if (!strncmp(c, "<![CDATA[", 9)) {

                goto store_content;
            } else if (*c == '<') {
                if (lws) {
                    if (elem->flags & LYXML_ELEM_MIXED) {

                        goto store_content;
                    } else {

                        lws = NULL;
                    }
                }
                if (elem->content) {

                    if (options & LYXML_PARSE_NOMIXEDCONTENT) {
                        LOGVAL(ctx, LYE_XML_INVAL, LY_VLOG_XML, elem, "XML element with mixed content");
                        goto error;
                    }
                    child = calloc(1, sizeof *child);
                    LY_CHECK_ERR_GOTO(!child, LOGMEM(ctx), error);
                    child->content = elem->content;
                    elem->content = NULL;
                    lyxml_add_child(ctx, elem, child);
                    elem->flags |= LYXML_ELEM_MIXED;
                }
                child = lyxml_parse_elem(ctx, c, &size, elem, options);
                if (!child) {
                    goto error;
                }
                c += size;
            } else if (is_xmlws(*c)) {
                lws = c;
                ign_xmlws(c);
            } else {
store_content:

                if (lws) {

                    c = lws;
                    lws = NULL;
                }
                str = parse_text(ctx, c, '<', &size);
                if (!str && !size) {
                    goto error;
                }
                elem->content = lydict_insert_zc(ctx, str);
                c += size;

                if (elem->child) {

                    if (options & LYXML_PARSE_NOMIXEDCONTENT) {
                        LOGVAL(ctx, LYE_XML_INVAL, LY_VLOG_XML, elem, "XML element with mixed content");
                        goto error;
                    }
                    child = calloc(1, sizeof *child);
                    LY_CHECK_ERR_GOTO(!child, LOGMEM(ctx), error);
                    child->content = elem->content;
                    elem->content = NULL;
                    lyxml_add_child(ctx, elem, child);
                    elem->flags |= LYXML_ELEM_MIXED;
                }
            }
        }
    } else {

        attr = parse_attr(ctx, c, &size, elem);
        if (!attr) {
            goto error;
        }
        c += size;


        if (attr->type == LYXML_ATTR_NS) {
            if ((!prefix || !prefix[0]) && !attr->name) {
                if (attr->value) {

                    elem->ns = (struct lyxml_ns *)attr;
                } else {

                    nons_flag = 1;
                }
            } else if (prefix && prefix[0] && attr->name && !strncmp(attr->name, prefix, prefix_len + 1)) {

                elem->ns = (struct lyxml_ns *)attr;
            }
        }


        goto process;
    }

    *len = c - data;

    if (!closed_flag) {
        LOGVAL(ctx, LYE_XML_MISS, LY_VLOG_XML, elem, "closing element tag", elem->name);
        goto error;
    }


    LY_TREE_FOR(elem->attr, attr) {
        if (attr->type == LYXML_ATTR_STD_UNRES) {
            str = (char *)attr->ns;
            attr->ns = lyxml_get_ns(elem, str);
            free(str);
            attr->type = LYXML_ATTR_STD;
        }
    }

    if (!elem->ns && !nons_flag && parent) {
        elem->ns = lyxml_get_ns(parent, prefix_len ? prefix : NULL);
    }
    free(prefix);
    return elem;

error:
    lyxml_free(ctx, elem);
    free(prefix);
    return NULL;
}
