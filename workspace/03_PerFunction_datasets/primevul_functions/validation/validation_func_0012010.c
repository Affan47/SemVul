lyxml_free_attr(struct ly_ctx *ctx, struct lyxml_elem *parent, struct lyxml_attr *attr)
{
    struct lyxml_attr *aiter, *aprev;

    if (!attr) {
        return;
    }

    if (parent) {

        aprev = NULL;
        for (aiter = parent->attr; aiter; aiter = aiter->next) {
            if (aiter == attr) {
                break;
            }
            aprev = aiter;
        }
        if (!aiter) {

            return;
        }

        if (!aprev) {

            parent->attr = attr->next;
        } else {

            aprev->next = attr->next;
        }
    }
    lydict_remove(ctx, attr->name);
    lydict_remove(ctx, attr->value);
    if (attr->type == LYXML_ATTR_STD_UNRES) {
        free((char *)attr->ns);
    }
    free(attr);
}
