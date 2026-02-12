check_default(struct lys_type *type, const char **value, struct lys_module *module, int tpdf)
{
    struct lys_tpdf *base_tpdf = NULL;
    struct lyd_node_leaf_list node;
    const char *dflt = NULL;
    char *s;
    int ret = EXIT_SUCCESS, r;
    struct ly_ctx *ctx = module->ctx;

    assert(value);
    memset(&node, 0, sizeof node);

    if (type->base <= LY_TYPE_DER) {

        ret = EXIT_FAILURE;
        goto cleanup;
    } else if (!tpdf && !module->implemented) {

        goto cleanup;
    } else if (tpdf && !module->implemented && type->base == LY_TYPE_IDENT) {


        if (*value) {
            if (strchr(*value, ':')) {
                dflt = transform_schema2json(module, *value);
            } else {

                if (asprintf(&s, "%s:%s", lys_main_module(module)->name, *value) == -1) {
                    LOGMEM(ctx);
                    ret = -1;
                    goto cleanup;
                }
                dflt = lydict_insert_zc(ctx, s);
            }
            lydict_remove(ctx, *value);
            *value = dflt;
            dflt = NULL;
        }
        goto cleanup;
    } else if (type->base == LY_TYPE_LEAFREF && tpdf) {

        goto cleanup;
    }

    dflt = lydict_insert(ctx, *value, 0);
    if (!dflt) {

        for (base_tpdf = type->der; base_tpdf->type.der; base_tpdf = base_tpdf->type.der) {
            if (base_tpdf->dflt) {
                dflt = lydict_insert(ctx, base_tpdf->dflt, 0);
                break;
            }
        }

        if (!dflt) {

            goto cleanup;
        }


        switch (type->base) {
        case LY_TYPE_IDENT:
            if (lys_main_module(base_tpdf->type.parent->module)->implemented) {
                goto cleanup;
            } else {


                module = base_tpdf->module;
            }
            break;
        case LY_TYPE_INST:
        case LY_TYPE_LEAFREF:
        case LY_TYPE_BOOL:
        case LY_TYPE_EMPTY:

            goto cleanup;
        case LY_TYPE_BITS:

            if (type->info.bits.count) {
                break;
            }
            goto cleanup;
        case LY_TYPE_ENUM:

            if (type->info.enums.count) {
                break;
            }
            goto cleanup;
        case LY_TYPE_DEC64:
            if (type->info.dec64.range) {
                break;
            }
            goto cleanup;
        case LY_TYPE_BINARY:
            if (type->info.binary.length) {
                break;
            }
            goto cleanup;
        case LY_TYPE_INT8:
        case LY_TYPE_INT16:
        case LY_TYPE_INT32:
        case LY_TYPE_INT64:
        case LY_TYPE_UINT8:
        case LY_TYPE_UINT16:
        case LY_TYPE_UINT32:
        case LY_TYPE_UINT64:
            if (type->info.num.range) {
                break;
            }
            goto cleanup;
        case LY_TYPE_STRING:
            if (type->info.str.length || type->info.str.patterns) {
                break;
            }
            goto cleanup;
        case LY_TYPE_UNION:

            break;
        default:
            LOGINT(ctx);
            ret = -1;
            goto cleanup;
        }
    } else if (type->base == LY_TYPE_EMPTY) {
        LOGVAL(ctx, LYE_INCHILDSTMT, LY_VLOG_NONE, NULL, "default", type->parent->name);
        LOGVAL(ctx, LYE_SPEC, LY_VLOG_NONE, NULL, "The \"empty\" data type cannot have a default value.");
        ret = -1;
        goto cleanup;
    }


    memset(&node, 0, sizeof node);
    node.value_str = lydict_insert(ctx, dflt, 0);
    node.value_type = type->base;

    if (tpdf) {
        node.schema = calloc(1, sizeof (struct lys_node_leaf));
        if (!node.schema) {
            LOGMEM(ctx);
            ret = -1;
            goto cleanup;
        }
        r = asprintf((char **)&node.schema->name, "typedef-%s-default", ((struct lys_tpdf *)type->parent)->name);
        if (r == -1) {
            LOGMEM(ctx);
            ret = -1;
            goto cleanup;
        }
        node.schema->module = module;
        memcpy(&((struct lys_node_leaf *)node.schema)->type, type, sizeof *type);
    } else {
        node.schema = (struct lys_node *)type->parent;
    }

    if (type->base == LY_TYPE_LEAFREF) {
        if (!type->info.lref.target) {
            ret = EXIT_FAILURE;
            LOGVAL(ctx, LYE_SPEC, LY_VLOG_NONE, NULL, "Default value \"%s\" cannot be checked in an unresolved leafref.",
                   dflt);
            goto cleanup;
        }
        ret = check_default(&type->info.lref.target->type, &dflt, module, 0);
        if (!ret) {

            if (*value) {
                lydict_remove(ctx, *value);
                *value = dflt;
                dflt = NULL;
            }
        }
    } else {
        if (!lyp_parse_value(type, &node.value_str, NULL, &node, NULL, module, 1, 1, 0)) {

            ret = EXIT_FAILURE;
            if (base_tpdf) {

                if ((type->base == LY_TYPE_BITS && type->der->type.der) ||
                        (type->base == LY_TYPE_ENUM && type->der->type.der)) {

                    LOGVAL(ctx, LYE_SPEC, LY_VLOG_NONE, NULL,
                           "Invalid value \"%s\" of the default statement inherited to \"%s\" from \"%s\" base type.",
                           dflt, type->parent->name, base_tpdf->name);
                }
            }
        } else {

            if (!ly_strequal(dflt, node.value_str, 1)) {


                assert(ly_strequal(dflt, *value, 1));

                lydict_remove(ctx, *value);
                *value = node.value_str;
                node.value_str = NULL;
            }
        }
    }

cleanup:
    lyd_free_value(node.value, node.value_type, node.value_flags, type, node.value_str, NULL, NULL, NULL);
    lydict_remove(ctx, node.value_str);
    if (tpdf && node.schema) {
        free((char *)node.schema->name);
        free(node.schema);
    }
    lydict_remove(ctx, dflt);

    return ret;
}
