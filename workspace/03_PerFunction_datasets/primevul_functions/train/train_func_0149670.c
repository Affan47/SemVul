yang_check_deviate_mandatory(struct lys_deviate *deviate, struct lys_node *dev_target)
{
    struct ly_ctx *ctx = dev_target->module->ctx;
    struct lys_node *parent;


    if (!(dev_target->nodetype & (LYS_LEAF | LYS_CHOICE | LYS_ANYDATA))) {
        LOGVAL(ctx, LYE_INSTMT, LY_VLOG_NONE, NULL, "mandatory");
        LOGVAL(ctx, LYE_SPEC, LY_VLOG_NONE, NULL, "Target node does not allow \"mandatory\" property.");
        goto error;
    }

    if (deviate->mod == LY_DEVIATE_ADD) {

        if (dev_target->flags & LYS_MAND_MASK) {
            LOGVAL(ctx, LYE_INSTMT, LY_VLOG_NONE, NULL, "mandatory");
            LOGVAL(ctx, LYE_SPEC, LY_VLOG_NONE, NULL, "Adding property that already exists.");
            goto error;
        } else {
            if (dev_target->nodetype == LYS_LEAF && ((struct lys_node_leaf *)dev_target)->dflt) {

                LOGVAL(ctx, LYE_INCHILDSTMT, LY_VLOG_NONE, NULL, "mandatory", "leaf");
                LOGVAL(ctx, LYE_SPEC, LY_VLOG_NONE, NULL, "The \"mandatory\" statement is forbidden on leaf with \"default\".");
                goto error;
            } else if (dev_target->nodetype == LYS_CHOICE && ((struct lys_node_choice *)dev_target)->dflt) {
                LOGVAL(ctx, LYE_INCHILDSTMT, LY_VLOG_NONE, NULL, "mandatory", "choice");
                LOGVAL(ctx, LYE_SPEC, LY_VLOG_NONE, NULL, "The \"mandatory\" statement is forbidden on choices with \"default\".");
                goto error;
            }
        }
    } else {
        if (!(dev_target->flags & LYS_MAND_MASK)) {
            LOGVAL(ctx, LYE_INSTMT, LY_VLOG_NONE, NULL, "mandatory");
            LOGVAL(ctx, LYE_SPEC, LY_VLOG_NONE, NULL, "Replacing a property that does not exist.");
            goto error;
        }
    }


    dev_target->flags &= ~LYS_MAND_MASK;


    dev_target->flags |= deviate->flags & LYS_MAND_MASK;


    for (parent = dev_target->parent;
         parent && !(parent->nodetype & (LYS_CHOICE | LYS_GROUPING | LYS_ACTION));
         parent = parent->parent) {
        if (parent->nodetype == LYS_CONTAINER && ((struct lys_node_container *)parent)->presence) {

            break;
        }
    }

    if (parent && parent->nodetype == LYS_CHOICE && ((struct lys_node_choice *)parent)->dflt) {
        if (lyp_check_mandatory_choice(parent)) {
            goto error;
        }
    }

    return EXIT_SUCCESS;

error:
    return EXIT_FAILURE;
}
