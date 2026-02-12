lyp_rfn_apply_ext(struct lys_module *module)
{
    int i, k, a = 0;
    struct lys_node *root, *nextroot, *next, *node;
    struct lys_node *target;
    struct lys_node_uses *uses;
    struct lys_refine *rfn;
    struct ly_set *extset;


    LY_TREE_FOR_SAFE(module->data, nextroot, root) {


        LY_TREE_DFS_BEGIN(root, next, node) {
            if (node->nodetype == LYS_USES) {
                uses = (struct lys_node_uses *)node;

                for (i = 0; i < uses->refine_size; i++) {
                    if (!uses->refine[i].ext_size) {

                        continue;
                    }
                    rfn = &uses->refine[i];


                    target = NULL;
                    resolve_descendant_schema_nodeid(rfn->target_name, uses->child,
                                                     LYS_NO_RPC_NOTIF_NODE | LYS_ACTION | LYS_NOTIF,
                                                     0, (const struct lys_node **)&target);
                    if (!target) {


                        LOGINT(module->ctx);;
                        return EXIT_FAILURE;
                    }


                    extset = ly_set_new();
                    k = -1;
                    while ((k = lys_ext_iter(rfn->ext, rfn->ext_size, k + 1, LYEXT_SUBSTMT_SELF)) != -1) {
                        ly_set_add(extset, rfn->ext[k]->def, 0);
                    }
                    for (k = 0; (unsigned int)k < extset->number; k++) {
                        if (lyp_rfn_apply_ext_(rfn, target, LYEXT_SUBSTMT_SELF, (struct lys_ext *)extset->set.g[k])) {
                            ly_set_free(extset);
                            return EXIT_FAILURE;
                        }
                    }
                    ly_set_free(extset);


                    if (rfn->dsc && lyp_rfn_apply_ext_(rfn, target, LYEXT_SUBSTMT_DESCRIPTION, NULL)) {
                        return EXIT_FAILURE;
                    }

                    if (rfn->ref && lyp_rfn_apply_ext_(rfn, target, LYEXT_SUBSTMT_REFERENCE, NULL)) {
                        return EXIT_FAILURE;
                    }


                    if ((rfn->flags & LYS_CONFIG_MASK) && (target->flags & LYS_CONFIG_MASK)) {
                        if (lyp_rfn_apply_ext_(rfn, target, LYEXT_SUBSTMT_CONFIG, NULL)) {
                            return EXIT_FAILURE;
                        }
                    }

                    if (rfn->dflt_size && lyp_rfn_apply_ext_(rfn, target, LYEXT_SUBSTMT_DEFAULT, NULL)) {
                        return EXIT_FAILURE;
                    }

                    if (rfn->flags & LYS_MAND_MASK) {
                        if (lyp_rfn_apply_ext_(rfn, target, LYEXT_SUBSTMT_MANDATORY, NULL)) {
                            return EXIT_FAILURE;
                        }
                    }

                    if ((target->nodetype & LYS_CONTAINER) && rfn->mod.presence) {
                        if (lyp_rfn_apply_ext_(rfn, target, LYEXT_SUBSTMT_PRESENCE, NULL)) {
                            return EXIT_FAILURE;
                        }
                    }

                    if (rfn->flags & LYS_RFN_MINSET) {
                        if (lyp_rfn_apply_ext_(rfn, target, LYEXT_SUBSTMT_MIN, NULL)) {
                            return EXIT_FAILURE;
                        }
                    }
                    if (rfn->flags & LYS_RFN_MAXSET) {
                        if (lyp_rfn_apply_ext_(rfn, target, LYEXT_SUBSTMT_MAX, NULL)) {
                            return EXIT_FAILURE;
                        }
                    }


                    if (target->ext_size) {


                        target->ext = realloc(target->ext, target->ext_size * sizeof *target->ext);
                    }
                }
            }
            LY_TREE_DFS_END(root, next, node)
        }

        if (!nextroot && a < module->augment_size) {
            nextroot = module->augment[a].child;
            a++;
        }
    }

    return EXIT_SUCCESS;
}
