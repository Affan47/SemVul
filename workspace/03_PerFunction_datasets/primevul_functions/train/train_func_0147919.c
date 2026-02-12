lyp_deviate_apply_ext(struct lys_deviate *dev, struct lys_node *target, LYEXT_SUBSTMT substmt, struct lys_ext *extdef)
{
    struct ly_ctx *ctx;
    int m, n;
    struct lys_ext_instance *new;
    void *reallocated;


    ctx = target->module->ctx;
    m = n = -1;

    while ((m = lys_ext_iter(dev->ext, dev->ext_size, m + 1, substmt)) != -1) {


        if (substmt == LYEXT_SUBSTMT_SELF && dev->ext[m]->def != extdef) {
            continue;
        }

        if (substmt == LYEXT_SUBSTMT_SELF && dev->mod == LY_DEVIATE_ADD) {

            do {
                n = lys_ext_iter(target->ext, target->ext_size, n + 1, substmt);
            } while (n != -1 && (target->ext[n]->def != extdef || !(target->ext[n]->flags & LYEXT_OPT_INHERIT)));
        } else {

            do {
                n = lys_ext_iter(target->ext, target->ext_size, n + 1, substmt);

            } while (n != -1 && substmt == LYEXT_SUBSTMT_SELF && target->ext[n]->def != extdef);
        }

        if (n == -1) {

            new = malloc(sizeof **target->ext);
            LY_CHECK_ERR_RETURN(!new, LOGMEM(ctx), EXIT_FAILURE);
            reallocated = realloc(target->ext, (target->ext_size + 1) * sizeof *target->ext);
            LY_CHECK_ERR_RETURN(!reallocated, LOGMEM(ctx); free(new), EXIT_FAILURE);
            target->ext = reallocated;
            target->ext_size++;

            n = target->ext_size - 1;
        } else {


            lys_extension_instances_free(ctx, target->ext[n]->ext, target->ext[n]->ext_size, NULL);
            lydict_remove(ctx, target->ext[n]->arg_value);
            free(target->ext[n]);


            new = malloc(sizeof **target->ext);
            LY_CHECK_ERR_RETURN(!new, LOGMEM(ctx), EXIT_FAILURE);
        }

        target->ext[n] = new;
        target->ext[n]->def = dev->ext[m]->def;
        target->ext[n]->arg_value = lydict_insert(ctx, dev->ext[m]->arg_value, 0);
        target->ext[n]->flags = 0;
        target->ext[n]->parent = target;
        target->ext[n]->parent_type = LYEXT_PAR_NODE;
        target->ext[n]->insubstmt = substmt;
        target->ext[n]->insubstmt_index = dev->ext[m]->insubstmt_index;
        target->ext[n]->ext_size = dev->ext[m]->ext_size;
        lys_ext_dup(ctx, target->module, dev->ext[m]->ext, dev->ext[m]->ext_size, target, LYEXT_PAR_NODE,
                    &target->ext[n]->ext, 1, NULL);
        target->ext[n]->nodetype = LYS_EXT;
        target->ext[n]->module = target->module;
        target->ext[n]->priv = NULL;


    }


    while ((n = lys_ext_iter(target->ext, target->ext_size, n + 1, substmt)) != -1) {
        if (substmt == LYEXT_SUBSTMT_SELF) {


            if (target->ext[n]->def != extdef ||
                    (dev->mod == LY_DEVIATE_ADD && !(target->ext[n]->flags & LYEXT_OPT_INHERIT))) {

                continue;
            }

        }


        lyp_ext_instance_rm(ctx, &target->ext, &target->ext_size, n);
        --n;
    }

    return EXIT_SUCCESS;
}
