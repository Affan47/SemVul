resolve_unres_schema_uses(struct lys_node_uses *uses, struct unres_schema *unres)
{
    int rc;
    struct lys_node *par_grp;
    struct ly_ctx *ctx = uses->module->ctx;


    for (par_grp = lys_parent((struct lys_node *)uses); par_grp && (par_grp->nodetype != LYS_GROUPING); par_grp = lys_parent(par_grp));
    if (par_grp && ly_strequal(par_grp->name, uses->name, 1)) {
        LOGVAL(ctx, LYE_INRESOLV, LY_VLOG_LYS, uses, "uses", uses->name);
        return -1;
    }

    if (!uses->grp) {
        rc = resolve_uses_schema_nodeid(uses->name, (const struct lys_node *)uses, (const struct lys_node_grp **)&uses->grp);
        if (rc == -1) {
            LOGVAL(ctx, LYE_INRESOLV, LY_VLOG_LYS, uses, "uses", uses->name);
            return -1;
        } else if (rc > 0) {
            LOGVAL(ctx, LYE_INCHAR, LY_VLOG_LYS, uses, uses->name[rc - 1], &uses->name[rc - 1]);
            return -1;
        } else if (!uses->grp) {
            if (par_grp && !(uses->flags & LYS_USESGRP)) {
                if (++((struct lys_node_grp *)par_grp)->unres_count == 0) {
                    LOGERR(ctx, LY_EINT, "Too many unresolved items (uses) inside a grouping.");
                    return -1;
                }
                uses->flags |= LYS_USESGRP;
            }
            LOGVAL(ctx, LYE_INRESOLV, LY_VLOG_LYS, uses, "uses", uses->name);
            return EXIT_FAILURE;
        }
    }

    if (uses->grp->unres_count) {
        if (par_grp && !(uses->flags & LYS_USESGRP)) {
            if (++((struct lys_node_grp *)par_grp)->unres_count == 0) {
                LOGERR(ctx, LY_EINT, "Too many unresolved items (uses) inside a grouping.");
                return -1;
            }
            uses->flags |= LYS_USESGRP;
        } else {

            uses->grp = NULL;
        }
        LOGVAL(ctx, LYE_INRESOLV, LY_VLOG_LYS, uses, "uses", uses->name);
        return EXIT_FAILURE;
    }

    rc = resolve_uses(uses, unres);
    if (!rc) {

        if (par_grp && (uses->flags & LYS_USESGRP)) {
            assert(((struct lys_node_grp *)par_grp)->unres_count);
            ((struct lys_node_grp *)par_grp)->unres_count--;
            uses->flags &= ~LYS_USESGRP;
        }


        if (lyp_check_status(uses->flags, uses->module, "of uses",
                         uses->grp->flags, uses->grp->module, uses->grp->name,
                         (struct lys_node *)uses)) {
            return -1;
        }

        return EXIT_SUCCESS;
    }

    return rc;
}
