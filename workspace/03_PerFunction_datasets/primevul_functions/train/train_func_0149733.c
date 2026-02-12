yang_fill_deviate_default(struct ly_ctx *ctx, struct lys_deviate *deviate, struct lys_node *dev_target,
                          struct ly_set *dflt_check, const char *value)
{
    struct lys_node *node;
    struct lys_node_choice *choice;
    struct lys_node_leaf *leaf;
    struct lys_node_leaflist *llist;
    int rc, i, j;
    unsigned int u;

    u = strlen(value);
    if (dev_target->nodetype == LYS_CHOICE) {
        choice = (struct lys_node_choice *)dev_target;
        rc = resolve_choice_default_schema_nodeid(value, choice->child, (const struct lys_node **)&node);
        if (rc || !node) {
            LOGVAL(ctx, LYE_INARG, LY_VLOG_NONE, NULL, value, "default");
            goto error;
        }
        if (deviate->mod == LY_DEVIATE_DEL) {
            if (!choice->dflt || (choice->dflt != node)) {
                LOGVAL(ctx, LYE_INARG, LY_VLOG_NONE, NULL, value, "default");
                LOGVAL(ctx, LYE_SPEC, LY_VLOG_NONE, NULL, "Value differs from the target being deleted.");
                goto error;
            }
            choice->dflt = NULL;

            j = -1;
            while ((j = lys_ext_iter(dev_target->ext, dev_target->ext_size, j + 1, LYEXT_SUBSTMT_DEFAULT)) != -1) {
                lyp_ext_instance_rm(ctx, &dev_target->ext, &dev_target->ext_size, j);
                --j;
            }
        } else {
            choice->dflt = node;
            if (!choice->dflt) {

                LOGVAL(ctx, LYE_INARG, LY_VLOG_NONE, NULL, value, "default");
                goto error;
            }
        }
    } else if (dev_target->nodetype == LYS_LEAF) {
        leaf = (struct lys_node_leaf *)dev_target;
        if (deviate->mod == LY_DEVIATE_DEL) {
            if (!leaf->dflt || !ly_strequal(leaf->dflt, value, 1)) {
                LOGVAL(ctx, LYE_INARG, LY_VLOG_NONE, NULL, value, "default");
                LOGVAL(ctx, LYE_SPEC, LY_VLOG_NONE, NULL, "Value differs from the target being deleted.");
                goto error;
            }

            lydict_remove(ctx, leaf->dflt);
            leaf->dflt = NULL;
            leaf->flags &= ~LYS_DFLTJSON;

            j = -1;
            while ((j = lys_ext_iter(dev_target->ext, dev_target->ext_size, j + 1, LYEXT_SUBSTMT_DEFAULT)) != -1) {
                lyp_ext_instance_rm(ctx, &dev_target->ext, &dev_target->ext_size, j);
                --j;
            }
        } else {

            lydict_remove(ctx, leaf->dflt);
            leaf->flags &= ~LYS_DFLTJSON;


            leaf->dflt = lydict_insert(ctx, value, u);


            ly_set_add(dflt_check, dev_target, 0);
        }
    } else {
        llist = (struct lys_node_leaflist *)dev_target;
        if (deviate->mod == LY_DEVIATE_DEL) {

            for (i = 0; i < llist->dflt_size; i++) {
                if (llist->dflt[i] && ly_strequal(llist->dflt[i], value, 1)) {

                    lydict_remove(llist->module->ctx, llist->dflt[i]);
                    llist->dflt[i] = NULL;

                    j = -1;
                    while ((j = lys_ext_iter(dev_target->ext, dev_target->ext_size, j + 1, LYEXT_SUBSTMT_DEFAULT)) != -1) {
                        if (dev_target->ext[j]->insubstmt_index == i) {
                            lyp_ext_instance_rm(ctx, &dev_target->ext, &dev_target->ext_size, j);
                            --j;
                        } else if (dev_target->ext[j]->insubstmt_index > i) {

                            dev_target->ext[j]->insubstmt_index--;
                        }
                    }
                    break;
                }
            }
            if (i == llist->dflt_size) {
                LOGVAL(ctx, LYE_INARG, LY_VLOG_NONE, NULL, value, "default");
                LOGVAL(ctx, LYE_SPEC, LY_VLOG_NONE, NULL, "The default value to delete not found in the target node.");
                goto error;
            }
        } else {


            for (i = 0; i < llist->dflt_size; i++) {
                if (ly_strequal(llist->dflt[i], value, 1)) {
                    LOGVAL(ctx, LYE_INARG, LY_VLOG_NONE, NULL, value, "default");
                    LOGVAL(ctx, LYE_SPEC, LY_VLOG_NONE, NULL, "Duplicated default value \"%s\".", value);
                    goto error;
                }
            }

            llist->dflt[llist->dflt_size++] = lydict_insert(ctx, value, u);


            ly_set_add(dflt_check, dev_target, 0);
            llist->flags &= ~LYS_DFLTJSON;
        }
    }

    return EXIT_SUCCESS;

error:
    return EXIT_FAILURE;
}
