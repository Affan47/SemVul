resolve_instid_predicate(const struct lys_module *prev_mod, const char *pred, struct lyd_node **node, int cur_idx)
{

    struct lyd_node_leaf_list *key;
    struct lys_node_leaf **list_keys = NULL;
    struct lys_node_list *slist = NULL;
    const char *model, *name, *value;
    int mod_len, nam_len, val_len, i, has_predicate, parsed;
    struct ly_ctx *ctx = prev_mod->ctx;

    assert(pred && node && *node);

    parsed = 0;
    do {
        if ((i = parse_predicate(pred + parsed, &model, &mod_len, &name, &nam_len, &value, &val_len, &has_predicate)) < 1) {
            return -parsed + i;
        }
        parsed += i;

        if (!(*node)) {

            continue;
        }


        if (name[0] == '.') {

            if ((*node)->schema->nodetype != LYS_LEAFLIST) {
                LOGVAL(ctx, LYE_SPEC, LY_VLOG_NONE, NULL, "Instance identifier expects leaf-list, but have %s \"%s\".",
                       strnodetype((*node)->schema->nodetype), (*node)->schema->name);
                parsed = -1;
                goto cleanup;
            }


            if (!valequal((*node)->schema, value, val_len, ((struct lyd_node_leaf_list *)*node)->value_str)) {
                *node = NULL;
                goto cleanup;
            }

        } else if (isdigit(name[0])) {
            assert(!value);


            if ((*node)->schema->nodetype != LYS_LIST) {
                LOGVAL(ctx, LYE_SPEC, LY_VLOG_NONE, NULL, "Instance identifier expects list, but have %s \"%s\".",
                       strnodetype((*node)->schema->nodetype), (*node)->schema->name);
                parsed = -1;
                goto cleanup;
            }

            if (((struct lys_node_list *)(*node)->schema)->keys) {
                LOGVAL(ctx, LYE_SPEC, LY_VLOG_NONE, NULL, "Instance identifier expects list without keys, but have list \"%s\".",
                       (*node)->schema->name);
                parsed = -1;
                goto cleanup;
            }


            if (atoi(name) != cur_idx) {
                *node = NULL;
                goto cleanup;
            }

        } else {

            if ((*node)->schema->nodetype != LYS_LIST) {
                LOGVAL(ctx, LYE_SPEC, LY_VLOG_NONE, NULL, "Instance identifier expects list, but have %s \"%s\".",
                       strnodetype((*node)->schema->nodetype), (*node)->schema->name);
                parsed = -1;
                goto cleanup;
            }
            slist = (struct lys_node_list *)(*node)->schema;


            if (!list_keys) {
                list_keys = malloc(slist->keys_size * sizeof *list_keys);
                LY_CHECK_ERR_RETURN(!list_keys, LOGMEM(ctx), -1);
                for (i = 0; i < slist->keys_size; ++i) {
                    list_keys[i] = slist->keys[i];
                }
            }


            for (i = 0; i < slist->keys_size; ++i) {
                if (list_keys[i] && !strncmp(list_keys[i]->name, name, nam_len) && !list_keys[i]->name[nam_len]) {
                    break;
                }
            }
            if (i == slist->keys_size) {

                LOGVAL(ctx, LYE_SPEC, LY_VLOG_NONE, NULL, "Instance identifier expects list with the key \"%.*s\","
                       " but list \"%s\" does not define it.", nam_len, name, slist->name);
                parsed = -1;
                goto cleanup;
            }


            if (model) {
                if (strncmp(list_keys[i]->module->name, model, mod_len) || list_keys[i]->module->name[mod_len]) {
                    LOGVAL(ctx, LYE_SPEC, LY_VLOG_NONE, NULL, "Instance identifier expects key \"%s\" from module \"%.*s\", not \"%s\".",
                           list_keys[i]->name, model, mod_len, list_keys[i]->module->name);
                    parsed = -1;
                    goto cleanup;
                }
            } else {
                if (list_keys[i]->module != prev_mod) {
                    LOGVAL(ctx, LYE_SPEC, LY_VLOG_NONE, NULL, "Instance identifier expects key \"%s\" from module \"%s\", not \"%s\".",
                           list_keys[i]->name, prev_mod->name, list_keys[i]->module->name);
                    parsed = -1;
                    goto cleanup;
                }
            }


            for (key = (struct lyd_node_leaf_list *)(*node)->child; key; key = (struct lyd_node_leaf_list *)key->next) {
                if (key->schema == (struct lys_node *)list_keys[i]) {
                    break;
                }
            }
            if (!key) {

                LOGINT(ctx);
                parsed = -1;
                goto cleanup;
            }


            if (!valequal(key->schema, value, val_len, key->value_str)) {
                *node = NULL;

                continue;
            }


            list_keys[i] = NULL;
        }
    } while (has_predicate);


    if (*node && list_keys) {
        for (i = 0; i < slist->keys_size; ++i) {
            if (list_keys[i]) {
                LOGVAL(ctx, LYE_SPEC, LY_VLOG_NONE, NULL, "Instance identifier is missing list key \"%s\".", list_keys[i]->name);
                parsed = -1;
                goto cleanup;
            }
        }
    }

cleanup:
    free(list_keys);
    return parsed;
}
