check_status_flag(struct lys_node *node, struct lys_node *parent)
{
    struct ly_ctx *ctx = node->module->ctx;
    char *str;

    if (node->nodetype & (LYS_OUTPUT | LYS_INPUT)) {
        return EXIT_SUCCESS;
    }

    if (parent && (parent->flags & (LYS_STATUS_DEPRC | LYS_STATUS_OBSLT))) {


        if (!(node->flags & (LYS_STATUS_MASK))) {

            str = lys_path(node, LYS_PATH_FIRST_PREFIX);
            LOGWRN(ctx, "Missing status in %s subtree (%s), inheriting.",
                   parent->flags & LYS_STATUS_DEPRC ? "deprecated" : "obsolete", str);
            free(str);
            node->flags |= parent->flags & LYS_STATUS_MASK;
        } else if ((parent->flags & LYS_STATUS_MASK) > (node->flags & LYS_STATUS_MASK)) {

            switch (node->flags & LYS_STATUS_MASK) {
                case 0:
                case LYS_STATUS_CURR:
                    LOGVAL(ctx, LYE_INSTATUS, LY_VLOG_LYS, parent, "current", strnodetype(node->nodetype), "is child of",
                           parent->flags & LYS_STATUS_DEPRC ? "deprecated" : "obsolete", parent->name);
                    break;
                case LYS_STATUS_DEPRC:
                    LOGVAL(ctx, LYE_INSTATUS, LY_VLOG_LYS, parent, "deprecated", strnodetype(node->nodetype), "is child of",
                           "obsolete", parent->name);
                    break;
            }
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}
