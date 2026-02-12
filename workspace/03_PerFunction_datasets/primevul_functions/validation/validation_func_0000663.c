lyxml_parse_mem(struct ly_ctx *ctx, const char *data, int options)
{
    FUN_IN;

    const char *c = data;
    unsigned int len;
    struct lyxml_elem *root, *first = NULL, *next;

    if (!ctx) {
        LOGARG;
        return NULL;
    }

    if (!data) {

        return NULL;
    }

repeat:

    while (1) {
        if (!*c) {

            return first;
        } else if (is_xmlws(*c)) {

            ign_xmlws(c);
        } else if (!strncmp(c, "<?", 2)) {

            c += 2;
            if (parse_ignore(ctx, c, "?>", &len)) {
                goto error;
            }
            c += len;
        } else if (!strncmp(c, "<!--", 4)) {

            c += 2;
            if (parse_ignore(ctx, c, "-->", &len)) {
                goto error;
            }
            c += len;
        } else if (!strncmp(c, "<!", 2)) {


            LOGERR(ctx, LY_EINVAL, "DOCTYPE not supported in XML documents.");
            goto error;
        } else if (*c == '<') {


            break;
        } else {
            LOGVAL(ctx, LYE_XML_INCHAR, LY_VLOG_NONE, NULL, c);
            goto error;
        }
    }

    root = lyxml_parse_elem(ctx, c, &len, NULL, options);
    if (!root) {
        goto error;
    } else if (!first) {
        first = root;
    } else {
        first->prev->next = root;
        root->prev = first->prev;
        first->prev = root;
    }
    c += len;


    ign_xmlws(c);
    if (*c) {
        if (options & LYXML_PARSE_MULTIROOT) {
            goto repeat;
        } else {
            LOGWRN(ctx, "There are some not parsed data:\n%s", c);
        }
    }

    return first;

error:
    LY_TREE_FOR_SAFE(first, next, root) {
        lyxml_free(ctx, root);
    }
    return NULL;
}
