lyxml_get_ns(const struct lyxml_elem *elem, const char *prefix)
{
    FUN_IN;

    struct lyxml_attr *attr;

    if (!elem) {
        return NULL;
    }

    for (attr = elem->attr; attr; attr = attr->next) {
        if (attr->type != LYXML_ATTR_NS) {
            continue;
        }
        if (!attr->name) {
            if (!prefix) {

                if (!attr->value) {

                    return NULL;
                }
                return (struct lyxml_ns *)attr;
            }
        } else if (prefix && !strcmp(attr->name, prefix)) {

            return (struct lyxml_ns *)attr;
        }
    }


    return lyxml_get_ns(elem->parent, prefix);
}
