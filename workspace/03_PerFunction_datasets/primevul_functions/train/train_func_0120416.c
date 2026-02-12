resolve_augment(struct lys_node_augment *aug, struct lys_node *uses, struct unres_schema *unres)
{
    int rc;
    struct lys_node *sub;
    struct lys_module *mod;
    struct ly_set *set;
    struct ly_ctx *ctx;

    assert(aug);
    mod = lys_main_module(aug->module);
    ctx = mod->ctx;


    aug->flags |= LYS_NOTAPPLIED;


    if (!aug->target) {

        rc = resolve_schema_nodeid(aug->target_name, uses, (uses ? NULL : lys_node_module((struct lys_node *)aug)), &set, 0, 0);
        if (rc == -1) {
            LOGVAL(ctx, LYE_PATH, LY_VLOG_LYS, aug);
            return -1;
        }
        if (!set) {
            LOGVAL(ctx, LYE_INRESOLV, LY_VLOG_LYS, aug, "augment", aug->target_name);
            return EXIT_FAILURE;
        }
        aug->target = set->set.s[0];
        ly_set_free(set);
    }


    if (mod->implemented && !lys_node_module(aug->target)->implemented) {
        lys_node_module(aug->target)->implemented = 1;
        if (unres_schema_add_node(lys_node_module(aug->target), unres, NULL, UNRES_MOD_IMPLEMENT, NULL) == -1) {
            return -1;
        }
    }


    if (!aug->parent && (lys_node_module((struct lys_node *)aug) != lys_node_module(aug->target))
            && (rc = lyp_check_mandatory_augment(aug, aug->target))) {
        return rc;
    }


    if (aug->target->nodetype & (LYS_CONTAINER | LYS_LIST)) {
        LY_TREE_FOR(aug->child, sub) {
            if (!(sub->nodetype & (LYS_ANYDATA | LYS_CONTAINER | LYS_LEAF | LYS_LIST | LYS_LEAFLIST | LYS_USES
                                   | LYS_CHOICE | LYS_ACTION | LYS_NOTIF))) {
                LOGVAL(ctx, LYE_INCHILDSTMT, LY_VLOG_LYS, aug, strnodetype(sub->nodetype), "augment");
                LOGVAL(ctx, LYE_SPEC, LY_VLOG_PREV, NULL, "Cannot augment \"%s\" with a \"%s\".",
                       strnodetype(aug->target->nodetype), strnodetype(sub->nodetype));
                return -1;
            }
        }
    } else if (aug->target->nodetype & (LYS_CASE | LYS_INPUT | LYS_OUTPUT | LYS_NOTIF)) {
        LY_TREE_FOR(aug->child, sub) {
            if (!(sub->nodetype & (LYS_ANYDATA | LYS_CONTAINER | LYS_LEAF | LYS_LIST | LYS_LEAFLIST | LYS_USES | LYS_CHOICE))) {
                LOGVAL(ctx, LYE_INCHILDSTMT, LY_VLOG_LYS, aug, strnodetype(sub->nodetype), "augment");
                LOGVAL(ctx, LYE_SPEC, LY_VLOG_PREV, NULL, "Cannot augment \"%s\" with a \"%s\".",
                       strnodetype(aug->target->nodetype), strnodetype(sub->nodetype));
                return -1;
            }
        }
    } else if (aug->target->nodetype == LYS_CHOICE) {
        LY_TREE_FOR(aug->child, sub) {
            if (!(sub->nodetype & (LYS_CASE | LYS_ANYDATA | LYS_CONTAINER | LYS_LEAF | LYS_LIST | LYS_LEAFLIST))) {
                LOGVAL(ctx, LYE_INCHILDSTMT, LY_VLOG_LYS, aug, strnodetype(sub->nodetype), "augment");
                LOGVAL(ctx, LYE_SPEC, LY_VLOG_PREV, NULL, "Cannot augment \"%s\" with a \"%s\".",
                       strnodetype(aug->target->nodetype), strnodetype(sub->nodetype));
                return -1;
            }
        }
    } else {
        LOGVAL(ctx, LYE_INARG, LY_VLOG_LYS, aug, aug->target_name, "target-node");
        LOGVAL(ctx, LYE_SPEC, LY_VLOG_PREV, NULL, "Invalid augment target node type \"%s\".", strnodetype(aug->target->nodetype));
        return -1;
    }


    LY_TREE_FOR(aug->child, sub) {
        if (lys_check_id(sub, aug->target, NULL)) {
            return -1;
        }
    }

    if (!aug->child) {

        LOGWRN(ctx, "Augment \"%s\" without children.", aug->target_name);
        aug->flags &= ~LYS_NOTAPPLIED;
    } else if ((aug->parent || mod->implemented) && apply_aug(aug, unres)) {


        return -1;
    }

    return EXIT_SUCCESS;
}
