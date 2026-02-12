resolve_partial_json_data_nodeid(const char *nodeid, const char *llist_value, struct lyd_node *start, int options,
                                 int *parsed)
{
    const char *id, *mod_name, *name, *data_val, *llval;
    int r, ret, mod_name_len, nam_len, is_relative = -1, list_instance_position;
    int has_predicate, last_parsed = 0, llval_len;
    struct lyd_node *sibling, *last_match = NULL;
    struct lyd_node_leaf_list *llist;
    const struct lys_module *prev_mod;
    struct ly_ctx *ctx;
    const struct lys_node *ssibling, *sparent;
    struct lys_node_list *slist;
    struct parsed_pred pp;

    assert(nodeid && start && parsed);

    memset(&pp, 0, sizeof pp);
    ctx = start->schema->module->ctx;
    id = nodeid;


    if ((r = parse_schema_nodeid(id, &mod_name, &mod_name_len, &name, &nam_len, &is_relative, NULL, NULL, 1)) < 1) {
        LOGVAL(ctx, LYE_PATH_INCHAR, LY_VLOG_NONE, NULL, id[-r], &id[-r]);
        goto error;
    }

    if (name[0] == '#') {
        if (is_relative) {
            LOGVAL(ctx, LYE_PATH_INCHAR, LY_VLOG_NONE, NULL, '#', name);
            goto error;
        }
        id += r;
        last_parsed = r;
    } else {
        is_relative = -1;
    }


    if ((r = parse_schema_nodeid(id, &mod_name, &mod_name_len, &name, &nam_len, &is_relative, &has_predicate, NULL, 0)) < 1) {
        LOGVAL(ctx, LYE_PATH_INCHAR, LY_VLOG_NONE, NULL, id[-r], &id[-r]);
        goto error;
    }
    id += r;

    last_parsed += r;

    if (is_relative) {
        prev_mod = lyd_node_module(start);
        start = (start->schema->nodetype & (LYS_CONTAINER | LYS_LIST | LYS_RPC | LYS_ACTION | LYS_NOTIF)) ? start->child : NULL;
    } else {
        for (; start->parent; start = start->parent);
        prev_mod = lyd_node_module(start);
    }
    if (!start) {

        return NULL;
    }


    goto parse_predicates;

    while (1) {

        ssibling = NULL;
        sparent = (start && start->parent) ? start->parent->schema : NULL;
        while ((ssibling = lys_getnext(ssibling, sparent, prev_mod, 0))) {

            if (sparent && (sparent->nodetype & (LYS_RPC | LYS_ACTION))) {
                if (options & LYD_PATH_OPT_OUTPUT) {
                    if (lys_parent(ssibling)->nodetype == LYS_INPUT) {
                        continue;
                    }
                } else {
                    if (lys_parent(ssibling)->nodetype == LYS_OUTPUT) {
                        continue;
                    }
                }
            }

            if (!schema_nodeid_siblingcheck(ssibling, prev_mod, mod_name, mod_name_len, name, nam_len)) {
                break;
            }
        }
        if (!ssibling) {

            free(pp.pred);
            return last_match;
        }
        pp.schema = ssibling;


        if (!id[0] && !pp.len && (ssibling->nodetype == LYS_LEAFLIST)) {
            pp.len = 1;
            pp.pred = calloc(1, sizeof *pp.pred);
            LY_CHECK_ERR_GOTO(!pp.pred, LOGMEM(ctx), error);

            pp.pred[0].name = ".";
            pp.pred[0].nam_len = 1;
            pp.pred[0].value = (llist_value ? llist_value : "");
            pp.pred[0].val_len = strlen(pp.pred[0].value);
        }

        if (ssibling->nodetype & (LYS_LEAFLIST | LYS_LEAF)) {

            if (pp.len > 1) {
                LOGVAL(ctx, LYE_PATH_PREDTOOMANY, LY_VLOG_NONE, NULL);
                goto error;
            } else if (pp.len) {
                if ((pp.pred[0].name[0] != '.') || (pp.pred[0].nam_len != 1)) {
                    LOGVAL(ctx, LYE_PATH_INCHAR, LY_VLOG_NONE, NULL, pp.pred[0].name[0], pp.pred[0].name);
                    goto error;
                }
                if ((((struct lys_node_leaf *)ssibling)->type.base == LY_TYPE_IDENT) && !strnchr(pp.pred[0].value, ':', pp.pred[0].val_len)) {
                    LOGVAL(ctx, LYE_PATH_INIDENTREF, LY_VLOG_LYS, ssibling, pp.pred[0].val_len, pp.pred[0].value);
                    goto error;
                }
            }
        } else if (ssibling->nodetype == LYS_LIST) {

            slist = (struct lys_node_list *)ssibling;
            if (!pp.len) {

                return last_match;
            } else if (!isdigit(pp.pred[0].name[0])) {

                if (pp.len > slist->keys_size) {
                    LOGVAL(ctx, LYE_PATH_PREDTOOMANY, LY_VLOG_NONE, NULL);
                    goto error;
                } else if (pp.len < slist->keys_size) {
                    LOGVAL(ctx, LYE_PATH_MISSKEY, LY_VLOG_NONE, NULL, slist->keys[pp.len]->name);
                    goto error;
                }

                for (r = 0; r < pp.len; ++r) {
                    if ((slist->keys[r]->type.base == LY_TYPE_IDENT) && !strnchr(pp.pred[r].value, ':', pp.pred[r].val_len)) {
                        LOGVAL(ctx, LYE_PATH_INIDENTREF, LY_VLOG_LYS, slist->keys[r], pp.pred[r].val_len, pp.pred[r].value);
                        goto error;
                    }
                }
            }
        } else if (pp.pred) {

            LOGVAL(ctx, LYE_PATH_PREDTOOMANY, LY_VLOG_NONE, NULL);
            goto error;
        }

#ifdef LY_ENABLED_CACHE

        if (start->parent && start->parent->ht && ((pp.schema->nodetype != LYS_LIST) || ((struct lys_node_list *)pp.schema)->keys_size)
                && ((pp.schema->nodetype != LYS_LEAFLIST) || (pp.schema->flags & LYS_CONFIG_W))) {
            sibling = resolve_json_data_node_hash(start->parent, pp);
        } else
#endif
        {
            list_instance_position = 0;
            LY_TREE_FOR(start, sibling) {

                if (lys_parent(sibling->schema)) {
                    if (options & LYD_PATH_OPT_OUTPUT) {
                        if (lys_parent(sibling->schema)->nodetype == LYS_INPUT) {
                            LOGERR(ctx, LY_EINVAL, "Provided data tree includes some RPC input nodes (%s).", sibling->schema->name);
                            goto error;
                        }
                    } else {
                        if (lys_parent(sibling->schema)->nodetype == LYS_OUTPUT) {
                            LOGERR(ctx, LY_EINVAL, "Provided data tree includes some RPC output nodes (%s).", sibling->schema->name);
                            goto error;
                        }
                    }
                }

                if (sibling->schema != ssibling) {

                    continue;
                }


                if (ssibling->nodetype == LYS_LEAFLIST) {
                    if (ssibling->flags & LYS_CONFIG_R) {

                        continue;
                    }

                    llist = (struct lyd_node_leaf_list *)sibling;


                    llval = NULL;
                    llval_len = 0;
                    if (pp.pred) {

                        llval = pp.pred[0].value;
                        llval_len = pp.pred[0].val_len;

                    }


                    if (llval && !strchr(llval, ':') && (llist->value_type & LY_TYPE_IDENT)
                            && !strncmp(llist->value_str, lyd_node_module(sibling)->name, strlen(lyd_node_module(sibling)->name))
                            && (llist->value_str[strlen(lyd_node_module(sibling)->name)] == ':')) {
                        data_val = llist->value_str + strlen(lyd_node_module(sibling)->name) + 1;
                    } else {
                        data_val = llist->value_str;
                    }

                    if ((!llval && data_val && data_val[0]) || (llval && (strncmp(llval, data_val, llval_len)
                            || data_val[llval_len]))) {
                        continue;
                    }

                } else if (ssibling->nodetype == LYS_LIST) {

                    ++list_instance_position;
                    ret = resolve_partial_json_data_list_predicate(pp, sibling, list_instance_position);
                    if (ret == -1) {
                        goto error;
                    } else if (ret == 1) {

                        continue;
                    }
                }

                break;
            }
        }


        if (!sibling) {
            free(pp.pred);
            return last_match;
        }


        *parsed += last_parsed;
        last_match = sibling;
        prev_mod = lyd_node_module(sibling);


        if (!id[0]) {
            free(pp.pred);
            return last_match;
        }


        if (ssibling->nodetype & (LYS_LEAF | LYS_LEAFLIST | LYS_ANYDATA)) {

            LOGVAL(ctx, LYE_PATH_INCHAR, LY_VLOG_NONE, NULL, id[0], id);
            goto error;
        } else if (!sibling->child) {

            free(pp.pred);
            return last_match;
        }
        start = sibling->child;


        if ((r = parse_schema_nodeid(id, &mod_name, &mod_name_len, &name, &nam_len, &is_relative, &has_predicate, NULL, 0)) < 1) {
            LOGVAL(ctx, LYE_PATH_INCHAR, LY_VLOG_NONE, NULL, id[-r], &id[-r]);
            goto error;
        }
        id += r;
        last_parsed = r;

parse_predicates:

        free(pp.pred);
        pp.schema = NULL;
        pp.len = 0;
        pp.pred = NULL;
        while (has_predicate) {
            ++pp.len;
            pp.pred = ly_realloc(pp.pred, pp.len * sizeof *pp.pred);
            LY_CHECK_ERR_GOTO(!pp.pred, LOGMEM(ctx), error);
            if ((r = parse_schema_json_predicate(id, &pp.pred[pp.len - 1].mod_name, &pp.pred[pp.len - 1].mod_name_len,
                                                 &pp.pred[pp.len - 1].name, &pp.pred[pp.len - 1].nam_len, &pp.pred[pp.len - 1].value,
                                                 &pp.pred[pp.len - 1].val_len, &has_predicate)) < 1) {
                LOGVAL(ctx, LYE_PATH_INCHAR, LY_VLOG_NONE, NULL, id[0], id);
                goto error;
            }

            id += r;
            last_parsed += r;
        }
    }

error:
    *parsed = -1;
    free(pp.pred);
    return NULL;
}
