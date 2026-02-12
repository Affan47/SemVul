resolve_identref(struct lys_type *type, const char *ident_name, struct lyd_node *node, struct lys_module *mod, int dflt)
{
    const char *mod_name, *name;
    char *str;
    int mod_name_len, nam_len, rc;
    int need_implemented = 0;
    unsigned int i, j;
    struct lys_ident *der, *cur;
    struct lys_module *imod = NULL, *m, *tmod;
    struct ly_ctx *ctx;

    assert(type && ident_name && mod);
    ctx = mod->ctx;

    if (!type || (!type->info.ident.count && !type->der) || !ident_name) {
        return NULL;
    }

    rc = parse_node_identifier(ident_name, &mod_name, &mod_name_len, &name, &nam_len, NULL, 0);
    if (rc < 1) {
        LOGVAL(ctx, LYE_INCHAR, node ? LY_VLOG_LYD : LY_VLOG_NONE, node, ident_name[-rc], &ident_name[-rc]);
        return NULL;
    } else if (rc < (signed)strlen(ident_name)) {
        LOGVAL(ctx, LYE_INCHAR, node ? LY_VLOG_LYD : LY_VLOG_NONE, node, ident_name[rc], &ident_name[rc]);
        return NULL;
    }

    m = lys_main_module(mod);
    if (!mod_name || (!strncmp(mod_name, m->name, mod_name_len) && !m->name[mod_name_len])) {

        imod = m;
    } else if (dflt) {


        for (i = 0; i < mod->imp_size; i++) {
            if (!strncmp(mod_name, mod->imp[i].module->name, mod_name_len) && !mod->imp[i].module->name[mod_name_len]) {
                imod = mod->imp[i].module;
                break;
            }
        }


        if (!imod && type && type->der) {
            tmod = type->der->module;
            for (i = 0; i < tmod->imp_size; i++) {
                if (!strncmp(mod_name, tmod->imp[i].module->name, mod_name_len) && !tmod->imp[i].module->name[mod_name_len]) {
                    imod = tmod->imp[i].module;
                    break;
                }
            }
        }
    } else {

        for (i = 0; i < (unsigned)mod->ctx->models.used; ++i) {
            imod = mod->ctx->models.list[i];
            if (!strncmp(mod_name, imod->name, mod_name_len) && !imod->name[mod_name_len]) {
                break;
            }
            imod = NULL;
        }
        if (!imod && mod->ctx->models.parsing_sub_modules_count) {


            for (i = 0; i < mod->ctx->models.parsing_sub_modules_count; i++) {
                imod = mod->ctx->models.parsing_sub_modules[i];
                if (imod->type) {

                    continue;
                }
                if (!strncmp(mod_name, imod->name, mod_name_len) && !imod->name[mod_name_len]) {
                    break;
                }
                imod = NULL;
            }
        }
    }

    if (!dflt && (!imod || !imod->implemented) && ctx->data_clb) {

        if (imod) {
            ctx->data_clb(ctx, imod->name, imod->ns, LY_MODCLB_NOT_IMPLEMENTED, ctx->data_clb_data);
        } else if (mod_name) {
            str = strndup(mod_name, mod_name_len);
            imod = (struct lys_module *)ctx->data_clb(ctx, str, NULL, 0, ctx->data_clb_data);
            free(str);
        }
    }
    if (!imod) {
        goto fail;
    }

    if (m != imod || lys_main_module(type->parent->module) != mod) {


        if (!imod->implemented) {
            cur = NULL;

            for (i = 0; i < imod->ident_size; i++) {
                if (!strcmp(name, imod->ident[i].name)) {
                    cur = &imod->ident[i];
                    break;
                }
            }
            if (!cur) {

                for (j = 0; j < imod->inc_size; j++) {
                    for (i = 0; i < imod->inc[j].submodule->ident_size; i++) {
                        if (!strcmp(name, imod->inc[j].submodule->ident[i].name)) {
                            cur = &imod->inc[j].submodule->ident[i];
                            break;
                        }
                    }
                }
                if (!cur) {
                    goto fail;
                }
            }


            while (type->der) {
                for (i = 0; i < type->info.ident.count; i++) {
                    if (search_base_identity(cur, type->info.ident.ref[i])) {

                        need_implemented = 1;
                        goto match;
                    }
                }
                type = &type->der->type;
            }

            LOGVAL(ctx, LYE_SPEC, node ? LY_VLOG_LYD : LY_VLOG_NONE, node, "Identity used as identityref value is not implemented.");
            goto fail;
        }
    }


    while (type->der) {
        for (i = 0; i < type->info.ident.count; ++i) {
            cur = type->info.ident.ref[i];

            if (cur->der) {

                for (j = 0; j < cur->der->number; j++) {
                    der = (struct lys_ident *)cur->der->set.g[j];
                    if (!strcmp(der->name, name) && lys_main_module(der->module) == imod) {

                        cur = der;
                        goto match;
                    }
                }
            }
        }
        type = &type->der->type;
    }

fail:
    LOGVAL(ctx, LYE_INRESOLV, node ? LY_VLOG_LYD : LY_VLOG_NONE, node, "identityref", ident_name);
    return NULL;

match:
    for (i = 0; i < cur->iffeature_size; i++) {
        if (!resolve_iffeature(&cur->iffeature[i])) {
            if (node) {
                LOGVAL(ctx, LYE_INVAL, LY_VLOG_LYD, node, cur->name, node->schema->name);
            }
            LOGVAL(ctx, LYE_SPEC, LY_VLOG_PREV, NULL, "Identity \"%s\" is disabled by its if-feature condition.", cur->name);
            return NULL;
        }
    }
    if (need_implemented) {
        if (dflt) {

            LOGVRB("Making \"%s\" module implemented because of identityref default value \"%s\" used in the implemented \"%s\" module",
                   imod->name, cur->name, mod->name);


            if (lys_set_implemented(imod)) {
                LOGERR(ctx, ly_errno, "Setting the module \"%s\" implemented because of used default identity \"%s\" failed.",
                       imod->name, cur->name);
                goto fail;
            }
        } else {

            LOGVAL(ctx, LYE_SPEC, LY_VLOG_NONE, NULL, "Identity found, but in a non-implemented module \"%s\".",
                   lys_main_module(cur->module)->name);
            goto fail;
        }
    }
    return cur;
}
