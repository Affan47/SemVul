lyxml_correct_attr_ns(struct ly_ctx *ctx, struct lyxml_attr *attr, struct lyxml_elem *attr_parent, int copy_ns)
{
    const struct lyxml_ns *tmp_ns;
    struct lyxml_elem *ns_root, *attr_root;

    if ((attr->type != LYXML_ATTR_NS) && attr->ns) {

        for (attr_root = attr_parent; attr_root->parent; attr_root = attr_root->parent);


        for (ns_root = attr->ns->parent; ns_root->parent; ns_root = ns_root->parent);


        if (ns_root != attr_root) {
            if (copy_ns) {
                tmp_ns = attr->ns;

                attr->ns = lyxml_get_ns(attr_parent, tmp_ns->prefix);


                if (!attr->ns) {
                    attr->ns = (struct lyxml_ns *)lyxml_dup_attr(ctx, attr_parent, (struct lyxml_attr *)tmp_ns);
                }
            } else {
                attr->ns = NULL;
            }
        }
    }
}
