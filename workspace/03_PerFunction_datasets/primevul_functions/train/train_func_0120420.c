resolve_base_ident(const struct lys_module *module, struct lys_ident *ident, const char *basename, const char *parent,
                   struct lys_type *type, struct unres_schema *unres)
{
    const char *name;
    int mod_name_len = 0, rc;
    struct lys_ident *target, **ret;
    uint16_t flags;
    struct lys_module *mod;
    struct ly_ctx *ctx = module->ctx;

    assert((ident && !type) || (!ident && type));

    if (!type) {

        ret = &target;
        flags = ident->flags;
        mod = ident->module;
    } else {

        ++type->info.ident.count;
        type->info.ident.ref = ly_realloc(type->info.ident.ref, type->info.ident.count * sizeof *type->info.ident.ref);
        LY_CHECK_ERR_RETURN(!type->info.ident.ref, LOGMEM(ctx), -1);

        ret = &type->info.ident.ref[type->info.ident.count - 1];
        flags = type->parent->flags;
        mod = type->parent->module;
    }
    *ret = NULL;


    name = strchr(basename, ':');
    if (name) {

        mod_name_len = name - basename;
        name++;

        if (!strncmp(basename, module->name, mod_name_len) && !module->name[mod_name_len]) {

            mod_name_len = 0;
        }
    } else {
        name = basename;
    }


    module = lyp_get_module(module, NULL, 0, mod_name_len ? basename : NULL, mod_name_len, 0);
    if (!module) {

        LOGVAL(ctx, LYE_INMOD, LY_VLOG_NONE, NULL, basename);
        return -1;
    }


    rc = resolve_base_ident_sub(module, ident, name, unres, ret);
    if (!rc) {
        assert(*ret);


        if (lyp_check_status(flags, mod, ident ? ident->name : "of type",
                             (*ret)->flags, (*ret)->module, (*ret)->name, NULL)) {
            rc = -1;
        } else if (ident) {
            ident->base[ident->base_size++] = *ret;
            if (lys_main_module(mod)->implemented) {


                resolve_identity_backlink_update(ident, *ret);
            }
        }
    } else if (rc == EXIT_FAILURE) {
        LOGVAL(ctx, LYE_INRESOLV, LY_VLOG_NONE, NULL, parent, basename);
        if (type) {
            --type->info.ident.count;
        }
    }

    return rc;
}
