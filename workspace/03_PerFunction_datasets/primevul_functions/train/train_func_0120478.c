resolve_partial_json_data_list_predicate(struct parsed_pred pp, struct lyd_node *node, int position)
{
    uint16_t i;
    struct lyd_node_leaf_list *key;
    struct lys_node_list *slist;
    struct ly_ctx *ctx;

    assert(node);
    assert(node->schema->nodetype == LYS_LIST);
    assert(pp.len);

    ctx = node->schema->module->ctx;
    slist = (struct lys_node_list *)node->schema;


    if (isdigit(pp.pred[0].name[0])) {
        if (position == atoi(pp.pred[0].name)) {

            return 0;
        } else {

            return 1;
        }
    }

    key = (struct lyd_node_leaf_list *)node->child;
    if (!key) {

        return 1;
    }


    for (i = 0; i < slist->keys_size; ++i) {
        if (strncmp(key->schema->name, pp.pred[i].name, pp.pred[i].nam_len) || key->schema->name[pp.pred[i].nam_len]) {
            LOGVAL(ctx, LYE_PATH_INKEY, LY_VLOG_NONE, NULL, pp.pred[i].name);
            return -1;
        }

        if (pp.pred[i].mod_name) {

            if (strncmp(lyd_node_module((struct lyd_node *)key)->name, pp.pred[i].mod_name, pp.pred[i].mod_name_len)
                    || lyd_node_module((struct lyd_node *)key)->name[pp.pred[i].mod_name_len]) {
                LOGVAL(ctx, LYE_PATH_INKEY, LY_VLOG_NONE, NULL, pp.pred[i].name);
                return -1;
            }


            if (lyd_node_module((struct lyd_node *)key) == lyd_node_module(node)) {
                LOGVAL(ctx, LYE_PATH_INKEY, LY_VLOG_NONE, NULL, pp.pred[i].name);
                return -1;
            }
        } else {

            if (lyd_node_module((struct lyd_node *)key) != lyd_node_module(node)) {
                LOGVAL(ctx, LYE_PATH_INKEY, LY_VLOG_NONE, NULL, pp.pred[i].name);
                return -1;
            }
        }


        if (strncmp(key->value_str, pp.pred[i].value, pp.pred[i].val_len) || key->value_str[pp.pred[i].val_len]) {
            return 1;
        }

        key = (struct lyd_node_leaf_list *)key->next;
    }

    return 0;
}
