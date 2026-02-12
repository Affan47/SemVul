resolve_when_unlink_nodes(struct lys_node *snode, struct lyd_node **node, struct lyd_node **ctx_node,
                          enum lyxp_node_type ctx_node_type, struct lyd_node **unlinked_nodes)
{
    struct lyd_node *next, *elem;
    const struct lys_node *slast;
    struct ly_ctx *ctx = snode->module->ctx;

    switch (snode->nodetype) {
    case LYS_AUGMENT:
    case LYS_USES:
    case LYS_CHOICE:
    case LYS_CASE:
        slast = NULL;
        while ((slast = lys_getnext(slast, snode, NULL, LYS_GETNEXT_PARENTUSES))) {
            if (slast->nodetype & (LYS_ACTION | LYS_NOTIF)) {
                continue;
            }

            if (resolve_when_unlink_nodes((struct lys_node *)slast, node, ctx_node, ctx_node_type, unlinked_nodes)) {
                return -1;
            }
        }
        break;
    case LYS_CONTAINER:
    case LYS_LIST:
    case LYS_LEAF:
    case LYS_LEAFLIST:
    case LYS_ANYXML:
    case LYS_ANYDATA:
        LY_TREE_FOR_SAFE(lyd_first_sibling(*node), next, elem) {
            if (elem->schema == snode) {

                if (elem == *ctx_node) {


                    if (ctx_node_type == LYXP_NODE_ELEM) {
                        LOGINT(ctx);
                        return -1;
                    }

                    if (elem->prev == elem) {

                        *ctx_node = NULL;
                    } else {

                        *ctx_node = elem->prev;
                    }
                } else if (elem == *node) {


                    if ((*node)->prev != *node) {
                        *node = (*node)->prev;
                    } else {

                        *node = NULL;
                    }
                }


                lyd_unlink_internal(elem, 0);
                if (*unlinked_nodes) {
                    if (lyd_insert_after((*unlinked_nodes)->prev, elem)) {
                        LOGINT(ctx);
                        return -1;
                    }
                } else {
                    *unlinked_nodes = elem;
                }

                if (snode->nodetype & (LYS_CONTAINER | LYS_LEAF | LYS_ANYDATA)) {

                    break;
                }
            }
        }
        break;
    default:
        LOGINT(ctx);
        return -1;
    }

    return EXIT_SUCCESS;
}
