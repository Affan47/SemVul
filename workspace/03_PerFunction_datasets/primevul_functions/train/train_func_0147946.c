lyp_check_import(struct lys_module *module, const char *value, struct lys_import *imp)
{
    int i;
    struct lys_module *dup = NULL;
    struct ly_ctx *ctx = module->ctx;


    for (i = 0; i < module->imp_size; i++) {
        if (!module->imp[i].module) {

            continue;
        }
        if (ly_strequal(module->imp[i].module->name, value, 1)) {

            if (imp->rev[0] && (!module->imp[i].module->rev_size || strcmp(module->imp[i].module->rev[0].date, imp->rev))) {


                LOGVAL(ctx, LYE_INARG, LY_VLOG_NONE, NULL, value, "import");
                LOGVAL(ctx, LYE_SPEC, LY_VLOG_NONE, NULL, "Importing multiple revisions of module \"%s\".", value);
                return -1;
            } else if (!imp->rev[0]) {


                dup = module->imp[i].module;
                break;
            }


            imp->module = module->imp[i].module;
            return 0;
        }
    }


    if (lyp_check_circmod(module, value, 1)) {
        return -1;
    }


    imp->module = (struct lys_module *)ly_ctx_load_sub_module(module->ctx, NULL, value, imp->rev[0] ? imp->rev : NULL,
                                                              module->ctx->models.flags & LY_CTX_ALLIMPLEMENTED ? 1 : 0,
                                                              NULL);


    if (!imp->module) {
        LOGERR(ctx, LY_EVALID, "Importing \"%s\" module into \"%s\" failed.", value, module->name);
        return -1;
    }

    if (imp->rev[0] && imp->module->rev_size && strcmp(imp->rev, imp->module->rev[0].date)) {
        LOGERR(ctx, LY_EVALID, "\"%s\" import of module \"%s\" in revision \"%s\" not found.",
               module->name, value, imp->rev);
        return -1;
    }

    if (dup) {

        if ((dup != imp->module) ||
                (dup->rev_size != imp->module->rev_size && (!dup->rev_size || imp->module->rev_size)) ||
                (dup->rev_size && strcmp(dup->rev[0].date, imp->module->rev[0].date))) {


            LOGVAL(ctx, LYE_INARG, LY_VLOG_NONE, NULL, value, "import");
            LOGVAL(ctx, LYE_SPEC, LY_VLOG_NONE, NULL, "Importing multiple revisions of module \"%s\".", value);
            return -1;
        } else {
            LOGWRN(ctx, "Module \"%s\" is imported by \"%s\" multiple times with different prefixes.", dup->name, module->name);
        }
    }

    return 0;
}
