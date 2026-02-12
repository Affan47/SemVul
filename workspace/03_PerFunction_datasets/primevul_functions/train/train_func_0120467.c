resolve_schema_leafref(struct lys_type *type, struct lys_node *parent, struct unres_schema *unres)
{
    const struct lys_node *node, *op_node = NULL, *tmp_parent;
    struct lys_node_augment *last_aug;
    const struct lys_module *tmp_mod, *cur_module;
    const char *id, *prefix, *name;
    int pref_len, nam_len, parent_times, has_predicate;
    int i, first_iter;
    struct ly_ctx *ctx = parent->module->ctx;

    if (!type->info.lref.target) {
        first_iter = 1;
        parent_times = 0;
        id = type->info.lref.path;


        for (op_node = lys_parent(parent);
            op_node && !(op_node->nodetype & (LYS_ACTION | LYS_NOTIF | LYS_RPC));
            op_node = lys_parent(op_node));

        cur_module = lys_node_module(parent);
        do {
            if ((i = parse_path_arg(cur_module, id, &prefix, &pref_len, &name, &nam_len, &parent_times, &has_predicate)) < 1) {
                LOGVAL(ctx, LYE_INCHAR, LY_VLOG_LYS, parent, id[-i], &id[-i]);
                return -1;
            }
            id += i;


            tmp_mod = prefix ? lyp_get_module(cur_module, NULL, 0, prefix, pref_len, 0) : cur_module;
            if (!tmp_mod) {
                LOGVAL(ctx, LYE_NORESOLV, LY_VLOG_LYS, parent, "leafref", type->info.lref.path);
                return EXIT_FAILURE;
            }
            last_aug = NULL;

            if (first_iter) {
                if (parent_times == -1) {

                    node = NULL;

                } else if (parent_times > 0) {

                    for (i = 0, node = parent; i < parent_times; i++) {
                        if (node->parent && (node->parent->nodetype == LYS_AUGMENT)
                                && !((struct lys_node_augment *)node->parent)->target) {

                            LOGVAL(ctx, LYE_SPEC, LY_VLOG_LYS, node->parent,
                                "Cannot resolve leafref \"%s\" because it is in an unresolved augment.", type->info.lref.path);
                            return EXIT_FAILURE;
                        }


                        for (node = lys_parent(node);
                            node && !(node->nodetype & (LYS_CONTAINER | LYS_LIST | LYS_ACTION | LYS_NOTIF | LYS_RPC));
                            node = lys_parent(node));

                        if (!node) {
                            if (i == parent_times - 1) {

                                break;
                            }


                            LOGVAL(ctx, LYE_NORESOLV, LY_VLOG_LYS, parent, "leafref", type->info.lref.path);
                            return EXIT_FAILURE;
                        }
                    }
                } else {
                    LOGINT(ctx);
                    return -1;
                }
            }


            if (!tmp_mod->implemented && node) {
    get_next_augment:
                last_aug = lys_getnext_target_aug(last_aug, tmp_mod, node);
            }

            tmp_parent = (last_aug ? (struct lys_node *)last_aug : node);
            node = NULL;
            while ((node = lys_getnext(node, tmp_parent, tmp_mod, LYS_GETNEXT_NOSTATECHECK))) {
                if (lys_node_module(node) != lys_main_module(tmp_mod)) {
                    continue;
                }
                if (strncmp(node->name, name, nam_len) || node->name[nam_len]) {
                    continue;
                }

                break;
            }
            if (!node) {
                if (last_aug) {

                    node = last_aug->target;
                    goto get_next_augment;
                }
                LOGVAL(ctx, LYE_NORESOLV, LY_VLOG_LYS, parent, "leafref", type->info.lref.path);
                return EXIT_FAILURE;
            }

            if (first_iter) {

                if (resolve_schema_leafref_valid_dep_flag(op_node, cur_module, node, (parent_times == -1 ? 1 : 0))) {
                    parent->flags |= LYS_LEAFREF_DEP;
                }
                first_iter = 0;
            }

            if (has_predicate) {

                if (node->nodetype != LYS_LIST) {
                    LOGVAL(ctx, LYE_NORESOLV, LY_VLOG_LYS, parent, "leafref", type->info.lref.path);
                    return -1;
                }

                i = resolve_schema_leafref_predicate(id, node, parent);
                if (!i) {
                    return EXIT_FAILURE;
                } else if (i < 0) {
                    return -1;
                }
                id += i;
                has_predicate = 0;
            }
        } while (id[0]);


        if ((node->nodetype != LYS_LEAF) && (node->nodetype != LYS_LEAFLIST)) {
            LOGVAL(ctx, LYE_NORESOLV, LY_VLOG_LYS, parent, "leafref", type->info.lref.path);
            LOGVAL(ctx, LYE_SPEC, LY_VLOG_PREV, NULL, "Leafref target \"%s\" is not a leaf nor a leaf-list.", type->info.lref.path);
            return -1;
        }


        if (lyp_check_status(parent->flags, parent->module, parent->name,
                        node->flags, node->module, node->name, node)) {
            return -1;
        }


        type->info.lref.target = (struct lys_node_leaf *)node;
    }


    if (lys_node_module(parent)->implemented) {

        for (node = (struct lys_node *)type->info.lref.target; node; node = lys_parent(node)) {
            if (!lys_node_module(node)->implemented) {
                lys_node_module(node)->implemented = 1;
                if (unres_schema_add_node(lys_node_module(node), unres, NULL, UNRES_MOD_IMPLEMENT, NULL) == -1) {
                    return -1;
                }
            }
        }


        if (lys_leaf_add_leafref_target(type->info.lref.target, (struct lys_node *)type->parent)) {
            return -1;
        }
    }


    return check_leafref_features(type);
}
