lyxml_dup_attr(struct ly_ctx *ctx, struct lyxml_elem *parent, struct lyxml_attr *attr)
{
    struct lyxml_attr *result, *a;

    if (!attr || !parent) {
        return NULL;
    }

    if (attr->type == LYXML_ATTR_NS) {


        result = (struct lyxml_attr *)calloc(1, sizeof (struct lyxml_ns));
    } else {
        result = calloc(1, sizeof (struct lyxml_attr));
    }
    LY_CHECK_ERR_RETURN(!result, LOGMEM(ctx), NULL);

    result->value = lydict_insert(ctx, attr->value, 0);
    result->name = lydict_insert(ctx, attr->name, 0);
    result->type = attr->type;


    if (result->type == LYXML_ATTR_STD && attr->ns) {
        result->ns = attr->ns;
        lyxml_correct_attr_ns(ctx, result, parent, 1);
    }


    if (result->type == LYXML_ATTR_NS) {
        ((struct lyxml_ns *)result)->parent = parent;
    }


    if (parent->attr) {

        for (a = parent->attr; a->next; a = a->next);

        a->next = result;
    } else {

        parent->attr = result;
    }

    return result;
}
