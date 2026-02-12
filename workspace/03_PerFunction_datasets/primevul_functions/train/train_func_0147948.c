lyp_rfn_apply_ext_(struct lys_refine *rfn, struct lys_node *target, LYEXT_SUBSTMT substmt, struct lys_ext *extdef)
{
    struct ly_ctx *ctx;
    int m, n;
    struct lys_ext_instance *new;
    void *reallocated;

    ctx = target->module->ctx;

    m = n = -1;
    while ((m = lys_ext_iter(rfn->ext, rfn->ext_size, m + 1, substmt)) != -1) {


        if (substmt == LYEXT_SUBSTMT_SELF && rfn->ext[m]->def != extdef) {
            continue;
        }


        do {
            n = lys_ext_iter(target->ext, target->ext_size, n + 1, substmt);
        } while (n != -1 && substmt == LYEXT_SUBSTMT_SELF && target->ext[n]->def != extdef);


        if (n == -1) {

            new = malloc(sizeof **target->ext);
            LY_CHECK_ERR_RETURN(!new, LOGMEM(ctx), EXIT_FAILURE);
            reallocated = realloc(target->ext, (target->ext_size + 1) * sizeof *target->ext);
            LY_CHECK_ERR_RETURN(!reallocated, LOGMEM(ctx); free(new), EXIT_FAILURE);
            target->ext = reallocated;
            target->ext_size++;


            n = target->ext_size - 1;
            target->ext[n] = new;
            target->ext[n]->parent = target;
            target->ext[n]->parent_type = LYEXT_PAR_NODE;
            target->ext[n]->flags = 0;
            target->ext[n]->insubstmt = substmt;
            target->ext[n]->priv = NULL;
            target->ext[n]->nodetype = LYS_EXT;
            target->ext[n]->module = target->module;
        } else {

            lys_extension_instances_free(ctx, target->ext[n]->ext, target->ext[n]->ext_size, NULL);
            lydict_remove(ctx, target->ext[n]->arg_value);
        }

        target->ext[n]->def = rfn->ext[m]->def;

        target->ext[n]->arg_value = lydict_insert(ctx, rfn->ext[m]->arg_value, 0);

        target->ext[n]->ext_size = rfn->ext[m]->ext_size;
        lys_ext_dup(ctx, target->module, rfn->ext[m]->ext, rfn->ext[m]->ext_size, target, LYEXT_PAR_NODE,
                    &target->ext[n]->ext, 0, NULL);

        target->ext[n]->insubstmt_index = rfn->ext[m]->insubstmt_index;
    }


    while ((n = lys_ext_iter(target->ext, target->ext_size, n + 1, substmt)) != -1) {
        if (substmt == LYEXT_SUBSTMT_SELF && target->ext[n]->def != extdef) {

            continue;
        }


        lyp_ext_instance_rm(ctx, &target->ext, &target->ext_size, n);
        --n;
    }

    return EXIT_SUCCESS;
}
