lyp_check_include_missing_recursive(struct lys_module *main_module, struct lys_submodule *sub)
{
    uint8_t i, j;
    void *reallocated;
    int ret = 0, tmp;
    struct ly_ctx *ctx = main_module->ctx;

    for (i = 0; i < sub->inc_size; i++) {

        for (j = 0; j < main_module->inc_size; j++) {
            if (main_module->inc[j].submodule == sub->inc[i].submodule) {
                break;
            }
        }

        if (j == main_module->inc_size) {

            if (main_module->version >= LYS_VERSION_1_1) {
                LOGVAL(ctx, LYE_MISSSTMT, LY_VLOG_NONE, NULL, "include");
                LOGVAL(ctx, LYE_SPEC, LY_VLOG_NONE, NULL,
                       "The main module \"%s\" misses include of the \"%s\" submodule used in another submodule \"%s\".",
                       main_module->name, sub->inc[i].submodule->name, sub->name);


                ret = 1;
            } else {

                LOGWRN(ctx, "The main module \"%s\" misses include of the \"%s\" submodule used in another submodule \"%s\".",
                       main_module->name, sub->inc[i].submodule->name, sub->name);
                LOGWRN(ctx, "To avoid further issues, adding submodule \"%s\" into the main module \"%s\".",
                       sub->inc[i].submodule->name, main_module->name);


            }
            main_module->inc_size++;
            reallocated = realloc(main_module->inc, main_module->inc_size * sizeof *main_module->inc);
            LY_CHECK_ERR_RETURN(!reallocated, LOGMEM(ctx), 1);
            main_module->inc = reallocated;
            memset(&main_module->inc[main_module->inc_size - 1], 0, sizeof *main_module->inc);


            memcpy(&main_module->inc[main_module->inc_size - 1].rev, sub->inc[i].rev, LY_REV_SIZE - 1);
            main_module->inc[main_module->inc_size - 1].submodule = sub->inc[i].submodule;
        }


        tmp = lyp_check_include_missing_recursive(main_module, sub->inc[i].submodule);
        if (!ret && tmp) {
            ret = 1;
        }
    }

    return ret;
}
