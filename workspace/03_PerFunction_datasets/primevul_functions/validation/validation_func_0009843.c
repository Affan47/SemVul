fill_yin_type(struct lys_module *module, struct lys_node *parent, struct lyxml_elem *yin, struct lys_type *type,
              int parenttype, struct unres_schema *unres)
{
    const char *value, *name, *module_name = NULL;
    struct lys_node *siter;
    struct lyxml_elem *next, *next2, *node, *child, exts;
    struct lys_restr **restrs, *restr;
    struct lys_type_bit bit, *bits_sc = NULL;
    struct lys_type_enum *enms_sc = NULL;
    struct lys_type *dertype;
    struct ly_ctx *ctx = module->ctx;
    int rc, val_set, c_ftrs, c_ext = 0;
    unsigned int i, j;
    int ret = -1;
    int64_t v, v_ = 0;
    int64_t p, p_;
    size_t len;
    int in_grp = 0;
    char *buf, modifier;


    memset(&exts, 0, sizeof exts);

    GETVAL(ctx, value, yin, "name");
    value = transform_schema2json(module, value);
    if (!value) {
        goto error;
    }

    i = parse_identifier(value);
    if (i < 1) {
        LOGVAL(ctx, LYE_INCHAR, LY_VLOG_NONE, NULL, value[-i], &value[-i]);
        lydict_remove(ctx, value);
        goto error;
    }

    name = value;
    if (value[i]) {
        module_name = lydict_insert(ctx, value, i);
        name += i;
        if ((name[0] != ':') || (parse_identifier(name + 1) < 1)) {
            LOGVAL(ctx, LYE_INCHAR, LY_VLOG_NONE, NULL, name[0], name);
            lydict_remove(ctx, module_name);
            lydict_remove(ctx, value);
            goto error;
        }

        ++name;
    }

    rc = resolve_superior_type(name, module_name, module, parent, &type->der);
    if (rc == -1) {
        LOGVAL(ctx, LYE_INMOD, LY_VLOG_NONE, NULL, module_name);
        lydict_remove(ctx, module_name);
        lydict_remove(ctx, value);
        goto error;


    } else if (rc == EXIT_FAILURE) {
        LOGVAL(ctx, LYE_NORESOLV, LY_VLOG_NONE, NULL, "type", name);
        lydict_remove(ctx, module_name);
        lydict_remove(ctx, value);
        ret = EXIT_FAILURE;
        goto error;
    }
    lydict_remove(ctx, module_name);
    lydict_remove(ctx, value);

    if (type->value_flags & LY_VALUE_UNRESGRP) {


        for (siter = parent; siter && (siter->nodetype != LYS_GROUPING); siter = lys_parent(siter));
        if (siter) {
            assert(((struct lys_node_grp *)siter)->unres_count);
            ((struct lys_node_grp *)siter)->unres_count--;
        } else {
            LOGINT(ctx);
            goto error;
        }
        type->value_flags &= ~LY_VALUE_UNRESGRP;
    }
    type->base = type->der->type.base;


    if (lyp_check_status(type->parent->flags, type->parent->module, type->parent->name,
                         type->der->flags, type->der->module, type->der->name,  parent)) {
        return -1;
    }


    LY_TREE_FOR_SAFE(yin->child, next, node) {
        if (!node->ns) {

            lyxml_free(ctx, node);
            continue;
        } else if (!strcmp(node->ns->value, LY_NSYIN)) {

            continue;
        }

        YIN_CHECK_ARRAY_OVERFLOW_GOTO(ctx, c_ext, type->ext_size, "extensions", "type", error);

        lyxml_unlink_elem(ctx, node, 2);
        lyxml_add_child(ctx, &exts, node);
        c_ext++;
    }
    if (c_ext) {
        type->ext = calloc(c_ext, sizeof *type->ext);
        LY_CHECK_ERR_GOTO(!type->ext, LOGMEM(ctx), error);

        LY_TREE_FOR_SAFE(exts.child, next, node) {
            rc = lyp_yin_fill_ext(type, LYEXT_PAR_TYPE, 0, 0, module, node, &type->ext, &type->ext_size, unres);
            if (rc) {
                goto error;
            }
        }

        lyp_reduce_ext_list(&type->ext, type->ext_size, c_ext + type->ext_size);
    }

    switch (type->base) {
    case LY_TYPE_BITS:


        LY_TREE_FOR_SAFE(yin->child, next, node) {
            if (!strcmp(node->name, "bit")) {
                YIN_CHECK_ARRAY_OVERFLOW_CODE(ctx, type->info.bits.count, type->info.bits.count, "bits", "type",
                                              type->info.bits.count = 0; goto error);
                type->info.bits.count++;
            } else {
                LOGVAL(ctx, LYE_INSTMT, LY_VLOG_NONE, NULL, node->name);
                type->info.bits.count = 0;
                goto error;
            }
        }
        dertype = &type->der->type;
        if (!dertype->der) {
            if (!type->info.bits.count) {

                LOGVAL(ctx, LYE_MISSCHILDSTMT, LY_VLOG_NONE, NULL, "bit", "type");
                goto error;
            }
        } else {
            for (; !dertype->info.enums.count; dertype = &dertype->der->type);
            if (module->version < 2 && type->info.bits.count) {


                LOGVAL(ctx, LYE_INSTMT, LY_VLOG_NONE, NULL, "bit");
                type->info.bits.count = 0;
                goto error;
            }
        }

        if (type->info.bits.count) {
            type->info.bits.bit = calloc(type->info.bits.count, sizeof *type->info.bits.bit);
            LY_CHECK_ERR_GOTO(!type->info.bits.bit, LOGMEM(ctx), error);
        }

        p = 0;
        i = 0;
        LY_TREE_FOR(yin->child, next) {
            c_ftrs = 0;

            GETVAL(ctx, value, next, "name");
            if (lyp_check_identifier(ctx, value, LY_IDENT_SIMPLE, NULL, NULL)) {
                goto error;
            }

            type->info.bits.bit[i].name = lydict_insert(ctx, value, strlen(value));
            if (read_yin_common(module, NULL, &type->info.bits.bit[i], LYEXT_PAR_TYPE_BIT, next, 0, unres)) {
                type->info.bits.count = i + 1;
                goto error;
            }

            if (!dertype->der) {

                for (j = 0; j < i; j++) {
                    if (!strcmp(type->info.bits.bit[j].name, type->info.bits.bit[i].name)) {
                        LOGVAL(ctx, LYE_BITS_DUPNAME, LY_VLOG_NONE, NULL, type->info.bits.bit[i].name);
                        type->info.bits.count = i + 1;
                        goto error;
                    }
                }
            } else {

                bits_sc = dertype->info.bits.bit;
                for (j = 0; j < dertype->info.bits.count; j++) {
                    if (ly_strequal(bits_sc[j].name, value, 1)) {
                        break;
                    }
                }
                if (j == dertype->info.bits.count) {
                    LOGVAL(ctx, LYE_BITS_INNAME, LY_VLOG_NONE, NULL, value);
                    type->info.bits.count = i + 1;
                    goto error;
                }
            }


            p_ = -1;
            LY_TREE_FOR_SAFE(next->child, next2, node) {
                if (!node->ns) {

                    continue;
                } else if (strcmp(node->ns->value, LY_NSYIN)) {

                    if (lyp_yin_parse_subnode_ext(module, &type->info.bits.bit[i], LYEXT_PAR_TYPE_BIT, node,
                                                  LYEXT_SUBSTMT_SELF, 0, unres)) {
                        goto error;
                    }
                } else if (!strcmp(node->name, "position")) {
                    if (p_ != -1) {
                        LOGVAL(ctx, LYE_TOOMANY, LY_VLOG_NONE, NULL, node->name, next->name);
                        type->info.bits.count = i + 1;
                        goto error;
                    }

                    GETVAL(ctx, value, node, "value");
                    p_ = strtoll(value, NULL, 10);


                    if (p_ < 0 || p_ > UINT32_MAX) {
                        LOGVAL(ctx, LYE_INARG, LY_VLOG_NONE, NULL, value, "bit/position");
                        type->info.bits.count = i + 1;
                        goto error;
                    }
                    type->info.bits.bit[i].pos = (uint32_t)p_;

                    if (!dertype->der) {

                        if (type->info.bits.bit[i].pos >= p) {
                            p = type->info.bits.bit[i].pos;
                            p++;
                        } else {

                            for (j = 0; j < i; j++) {
                                if (type->info.bits.bit[j].pos == type->info.bits.bit[i].pos) {
                                    LOGVAL(ctx, LYE_BITS_DUPVAL, LY_VLOG_NONE, NULL,
                                           type->info.bits.bit[i].pos, type->info.bits.bit[i].name,
                                           type->info.bits.bit[j].name);
                                    type->info.bits.count = i + 1;
                                    goto error;
                                }
                            }
                        }
                    }

                    if (lyp_yin_parse_subnode_ext(module, &type->info.bits.bit[i], LYEXT_PAR_TYPE_BIT, node,
                                             LYEXT_SUBSTMT_POSITION, 0, unres)) {
                        goto error;
                    }

                    for (j = 0; j < type->info.bits.bit[i].ext_size; ++j) {

                        if (type->info.bits.bit[i].ext[j]->flags & LYEXT_OPT_VALID) {
                            type->parent->flags |= LYS_VALID_EXT;
                            break;
                        }
                    }

                } else if ((module->version >= 2) && !strcmp(node->name, "if-feature")) {
                    YIN_CHECK_ARRAY_OVERFLOW_GOTO(ctx, c_ftrs, type->info.bits.bit[i].iffeature_size, "if-features", "bit", error);
                    c_ftrs++;
                } else {
                    LOGVAL(ctx, LYE_INSTMT, LY_VLOG_NONE, NULL, node->name);
                    goto error;
                }
            }

            if (!dertype->der) {
                if (p_ == -1) {

                    if (p > UINT32_MAX) {
                        LOGVAL(ctx, LYE_INARG, LY_VLOG_NONE, NULL, "4294967295", "bit/position");
                        type->info.bits.count = i + 1;
                        goto error;
                    }
                    type->info.bits.bit[i].pos = (uint32_t)p;
                    type->info.bits.bit[i].flags |= LYS_AUTOASSIGNED;
                    p++;
                }
            } else {
                if (p_ == -1) {

                    type->info.bits.bit[i].pos = bits_sc[j].pos;
                    type->info.bits.bit[i].flags |= LYS_AUTOASSIGNED;
                } else {


                    if (p_ != bits_sc[j].pos) {


                        LOGVAL(ctx, LYE_BITS_INVAL, LY_VLOG_NONE, NULL, type->info.bits.bit[i].pos,
                               type->info.bits.bit[i].name, bits_sc[j].pos);
                        type->info.bits.count = i + 1;
                        goto error;
                    }
                }
            }


            if (c_ftrs) {
                bits_sc = &type->info.bits.bit[i];
                bits_sc->iffeature = calloc(c_ftrs, sizeof *bits_sc->iffeature);
                if (!bits_sc->iffeature) {
                    LOGMEM(ctx);
                    type->info.bits.count = i + 1;
                    goto error;
                }

                LY_TREE_FOR(next->child, node) {
                    if (!strcmp(node->name, "if-feature")) {
                        rc = fill_yin_iffeature((struct lys_node *)type->parent, 0, node,
                                                &bits_sc->iffeature[bits_sc->iffeature_size], unres);
                        bits_sc->iffeature_size++;
                        if (rc) {
                            type->info.bits.count = i + 1;
                            goto error;
                        }
                    }
                }
            }


            j = i;
            while (j && type->info.bits.bit[j - 1].pos > type->info.bits.bit[j].pos) {

                memcpy(&bit, &type->info.bits.bit[j], sizeof bit);
                memcpy(&type->info.bits.bit[j], &type->info.bits.bit[j - 1], sizeof bit);
                memcpy(&type->info.bits.bit[j - 1], &bit, sizeof bit);
                j--;
            }

            ++i;
        }
        break;

    case LY_TYPE_DEC64:

        LY_TREE_FOR(yin->child, node) {

            if (!strcmp(node->name, "range")) {
                if (type->info.dec64.range) {
                    LOGVAL(ctx, LYE_TOOMANY, LY_VLOG_NONE, NULL, node->name, yin->name);
                    goto error;
                }

                GETVAL(ctx, value, node, "value");
                type->info.dec64.range = calloc(1, sizeof *type->info.dec64.range);
                LY_CHECK_ERR_GOTO(!type->info.dec64.range, LOGMEM(ctx), error);
                type->info.dec64.range->expr = lydict_insert(ctx, value, 0);


                if (read_restr_substmt(module, type->info.dec64.range, node, unres)) {
                    goto error;
                }
                for (j = 0; j < type->info.dec64.range->ext_size; ++j) {

                    if (type->info.dec64.range->ext[j]->flags & LYEXT_OPT_VALID) {
                        type->parent->flags |= LYS_VALID_EXT;
                        break;
                    }
                }
            } else if (!strcmp(node->name, "fraction-digits")) {
                if (type->info.dec64.dig) {
                    LOGVAL(ctx, LYE_TOOMANY, LY_VLOG_NONE, NULL, node->name, yin->name);
                    goto error;
                }
                GETVAL(ctx, value, node, "value");
                v = strtol(value, NULL, 10);


                if (v < 1 || v > 18) {
                    LOGVAL(ctx, LYE_INARG, LY_VLOG_NONE, NULL, value, node->name);
                    goto error;
                }
                type->info.dec64.dig = (uint8_t)v;
                type->info.dec64.div = 10;
                for (i = 1; i < v; i++) {
                    type->info.dec64.div *= 10;
                }


                if (lyp_yin_parse_subnode_ext(module, type, LYEXT_PAR_TYPE, node, LYEXT_SUBSTMT_DIGITS, 0, unres)) {
                    goto error;
                }
            } else {
                LOGVAL(ctx, LYE_INSTMT, LY_VLOG_NONE, NULL, node->name);
                goto error;
            }
        }


        if (!type->info.dec64.dig && !type->der->type.der) {

            LOGVAL(ctx, LYE_MISSCHILDSTMT, LY_VLOG_NONE, NULL, "fraction-digits", "type");
            goto error;
        }
        if (type->info.dec64.dig && type->der->type.der) {

            LOGVAL(ctx, LYE_INSTMT, LY_VLOG_NONE, NULL, "fraction-digits");
            goto error;
        }


        if (type->der->type.der) {
            type->info.dec64.dig = type->der->type.info.dec64.dig;
            type->info.dec64.div = type->der->type.info.dec64.div;
        }

        if (type->info.dec64.range && lyp_check_length_range(ctx, type->info.dec64.range->expr, type)) {
            LOGVAL(ctx, LYE_INARG, LY_VLOG_NONE, NULL, value, "range");
            goto error;
        }
        break;

    case LY_TYPE_ENUM:


        LY_TREE_FOR_SAFE(yin->child, next, node) {

            if (!strcmp(node->name, "enum")) {
                YIN_CHECK_ARRAY_OVERFLOW_CODE(ctx, type->info.enums.count, type->info.enums.count, "enums", "type",
                                              type->info.enums.count = 0; goto error);
                type->info.enums.count++;
            } else {
                LOGVAL(ctx, LYE_INSTMT, LY_VLOG_NONE, NULL, node->name);
                type->info.enums.count = 0;
                goto error;
            }
        }
        dertype = &type->der->type;
        if (!dertype->der) {
            if (!type->info.enums.count) {

                LOGVAL(ctx, LYE_MISSCHILDSTMT, LY_VLOG_NONE, NULL, "enum", "type");
                goto error;
            }
        } else {
            for (; !dertype->info.enums.count; dertype = &dertype->der->type);
            if (module->version < 2 && type->info.enums.count) {


                LOGVAL(ctx, LYE_INSTMT, LY_VLOG_NONE, NULL, "enum");
                type->info.enums.count = 0;
                goto error;
            }
        }

        if (type->info.enums.count) {
            type->info.enums.enm = calloc(type->info.enums.count, sizeof *type->info.enums.enm);
            LY_CHECK_ERR_GOTO(!type->info.enums.enm, LOGMEM(ctx), error);
        }

        v = 0;
        i = 0;
        LY_TREE_FOR(yin->child, next) {
            c_ftrs = 0;

            GETVAL(ctx, value, next, "name");
            if (!value[0]) {
                LOGVAL(ctx, LYE_INARG, LY_VLOG_NONE, NULL, value, "enum name");
                LOGVAL(ctx, LYE_SPEC, LY_VLOG_NONE, NULL, "Enum name must not be empty.");
                goto error;
            }
            type->info.enums.enm[i].name = lydict_insert(ctx, value, strlen(value));
            if (read_yin_common(module, NULL, &type->info.enums.enm[i], LYEXT_PAR_TYPE_ENUM, next, 0, unres)) {
                type->info.enums.count = i + 1;
                goto error;
            }


            value = type->info.enums.enm[i].name;
            if (isspace(value[0]) || isspace(value[strlen(value) - 1])) {
                LOGVAL(ctx, LYE_ENUM_WS, LY_VLOG_NONE, NULL, value);
                type->info.enums.count = i + 1;
                goto error;
            }

            if (!dertype->der) {

                for (j = 0; j < i; j++) {
                    if (ly_strequal(type->info.enums.enm[j].name, value, 1)) {
                        LOGVAL(ctx, LYE_ENUM_DUPNAME, LY_VLOG_NONE, NULL, value);
                        type->info.enums.count = i + 1;
                        goto error;
                    }
                }
            } else {

                enms_sc = dertype->info.enums.enm;
                for (j = 0; j < dertype->info.enums.count; j++) {
                    if (ly_strequal(enms_sc[j].name, value, 1)) {
                        break;
                    }
                }
                if (j == dertype->info.enums.count) {
                    LOGVAL(ctx, LYE_ENUM_INNAME, LY_VLOG_NONE, NULL, value);
                    type->info.enums.count = i + 1;
                    goto error;
                }
            }

            val_set = 0;
            LY_TREE_FOR_SAFE(next->child, next2, node) {
                if (!node->ns) {

                    continue;
                } else if (strcmp(node->ns->value, LY_NSYIN)) {

                    if (lyp_yin_parse_subnode_ext(module, &type->info.enums.enm[i], LYEXT_PAR_TYPE_ENUM, node,
                                             LYEXT_SUBSTMT_SELF, 0, unres)) {
                        goto error;
                    }
                } else if (!strcmp(node->name, "value")) {
                    if (val_set) {
                        LOGVAL(ctx, LYE_TOOMANY, LY_VLOG_NONE, NULL, node->name, next->name);
                        type->info.enums.count = i + 1;
                        goto error;
                    }

                    GETVAL(ctx, value, node, "value");
                    v_ = strtoll(value, NULL, 10);


                    if (v_ < INT32_MIN || v_ > INT32_MAX) {
                        LOGVAL(ctx, LYE_INARG, LY_VLOG_NONE, NULL, value, "enum/value");
                        type->info.enums.count = i + 1;
                        goto error;
                    }
                    type->info.enums.enm[i].value = v_;

                    if (!dertype->der) {
                        if (!i) {

                            v = type->info.enums.enm[i].value;
                            v++;
                        } else {

                            if (type->info.enums.enm[i].value >= v) {
                                v = type->info.enums.enm[i].value;
                                v++;
                            } else {

                                for (j = 0; j < i; j++) {
                                    if (type->info.enums.enm[j].value == type->info.enums.enm[i].value) {
                                        LOGVAL(ctx, LYE_ENUM_DUPVAL, LY_VLOG_NONE, NULL,
                                               type->info.enums.enm[i].value, type->info.enums.enm[i].name,
                                               type->info.enums.enm[j].name);
                                        type->info.enums.count = i + 1;
                                        goto error;
                                    }
                                }
                            }
                        }
                    }
                    val_set = 1;

                    if (lyp_yin_parse_subnode_ext(module, &type->info.enums.enm[i], LYEXT_PAR_TYPE_ENUM, node,
                                             LYEXT_SUBSTMT_VALUE, 0, unres)) {
                        goto error;
                    }

                    for (j = 0; j < type->info.enums.enm[i].ext_size; ++j) {

                        if (type->info.enums.enm[i].ext[j]->flags & LYEXT_OPT_VALID) {
                            type->parent->flags |= LYS_VALID_EXT;
                            break;
                        }
                    }
                } else if ((module->version >= 2) && !strcmp(node->name, "if-feature")) {
                    YIN_CHECK_ARRAY_OVERFLOW_GOTO(ctx, c_ftrs, type->info.enums.enm[i].iffeature_size, "if-features", "enum", error);
                    c_ftrs++;

                } else {
                    LOGVAL(ctx, LYE_INSTMT, LY_VLOG_NONE, NULL, node->name);
                    goto error;
                }
            }

            if (!dertype->der) {
                if (!val_set) {

                    if (v > INT32_MAX) {
                        LOGVAL(ctx, LYE_INARG, LY_VLOG_NONE, NULL, "2147483648", "enum/value");
                        type->info.enums.count = i + 1;
                        goto error;
                    }
                    type->info.enums.enm[i].value = v;
                    type->info.enums.enm[i].flags |= LYS_AUTOASSIGNED;
                    v++;
                }
            } else {
                if (!val_set) {

                    type->info.enums.enm[i].value = enms_sc[j].value;
                    type->info.enums.enm[i].flags |= LYS_AUTOASSIGNED;
                } else {


                    if (v_ != enms_sc[j].value) {


                        LOGVAL(ctx, LYE_ENUM_INVAL, LY_VLOG_NONE, NULL,
                               type->info.enums.enm[i].value, type->info.enums.enm[i].name, enms_sc[j].value);
                        type->info.enums.count = i + 1;
                        goto error;
                    }
                }
            }


            if (c_ftrs) {
                enms_sc = &type->info.enums.enm[i];
                enms_sc->iffeature = calloc(c_ftrs, sizeof *enms_sc->iffeature);
                if (!enms_sc->iffeature) {
                    LOGMEM(ctx);
                    type->info.enums.count = i + 1;
                    goto error;
                }

                LY_TREE_FOR(next->child, node) {
                    if (!strcmp(node->name, "if-feature")) {
                        rc = fill_yin_iffeature((struct lys_node *)type->parent, 0, node,
                                                &enms_sc->iffeature[enms_sc->iffeature_size], unres);
                        enms_sc->iffeature_size++;
                        if (rc) {
                            type->info.enums.count = i + 1;
                            goto error;
                        }
                    }
                }
            }

            ++i;
        }
        break;

    case LY_TYPE_IDENT:


        LY_TREE_FOR_SAFE(yin->child, next, node) {

            if (strcmp(node->name, "base")) {
                LOGVAL(ctx, LYE_INSTMT, LY_VLOG_NONE, NULL, node->name);
                goto error;
            }

            GETVAL(ctx, value, yin->child, "name");

            value = transform_schema2json(module, value);
            if (!value) {
                goto error;
            }
            rc = unres_schema_add_str(module, unres, type, UNRES_TYPE_IDENTREF, value);
            lydict_remove(ctx, value);
            if (rc == -1) {
                goto error;
            }

            if (lyp_yin_parse_subnode_ext(module, type, LYEXT_PAR_TYPE, node, LYEXT_SUBSTMT_BASE, 0, unres)) {
                goto error;
            }
        }

        if (!yin->child) {
            if (type->der->type.der) {

                break;
            }
            LOGVAL(ctx, LYE_MISSCHILDSTMT, LY_VLOG_NONE, NULL, "base", "type");
            goto error;
        } else {
            if (type->der->type.der) {
                LOGVAL(ctx, LYE_INSTMT, LY_VLOG_NONE, NULL, "base");
                goto error;
            }
        }
        if (yin->child->next) {
            LOGVAL(ctx, LYE_TOOMANY, LY_VLOG_NONE, NULL, yin->child->next->name, yin->name);
            goto error;
        }
        break;

    case LY_TYPE_INST:

        LY_TREE_FOR(yin->child, node) {
            if (!strcmp(node->name, "require-instance")) {
                if (type->info.inst.req) {
                    LOGVAL(ctx, LYE_TOOMANY, LY_VLOG_NONE, NULL, node->name, yin->name);
                    goto error;
                }
                GETVAL(ctx, value, node, "value");
                if (!strcmp(value, "true")) {
                    type->info.inst.req = 1;
                } else if (!strcmp(value, "false")) {
                    type->info.inst.req = -1;
                } else {
                    LOGVAL(ctx, LYE_INARG, LY_VLOG_NONE, NULL, value, node->name);
                    goto error;
                }


                if (lyp_yin_parse_subnode_ext(module, type, LYEXT_PAR_TYPE, node, LYEXT_SUBSTMT_REQINSTANCE, 0, unres)) {
                    goto error;
                }
            } else {
                LOGVAL(ctx, LYE_INSTMT, LY_VLOG_NONE, NULL, node->name);
                goto error;
            }
        }

        if (type->der->type.der && !type->info.inst.req) {

            type->info.inst.req = type->der->type.info.inst.req;
        }

        break;

    case LY_TYPE_BINARY:

    case LY_TYPE_INT8:
    case LY_TYPE_INT16:
    case LY_TYPE_INT32:
    case LY_TYPE_INT64:
    case LY_TYPE_UINT8:
    case LY_TYPE_UINT16:
    case LY_TYPE_UINT32:
    case LY_TYPE_UINT64:


        if (type->base == LY_TYPE_BINARY) {
            restrs = &type->info.binary.length;
            name = "length";
        } else {
            restrs = &type->info.num.range;
            name = "range";
        }

        LY_TREE_FOR(yin->child, node) {

            if (!strcmp(node->name, name)) {
                if (*restrs) {
                    LOGVAL(ctx, LYE_TOOMANY, LY_VLOG_NONE, NULL, node->name, yin->name);
                    goto error;
                }

                GETVAL(ctx, value, node, "value");
                if (lyp_check_length_range(ctx, value, type)) {
                    LOGVAL(ctx, LYE_INARG, LY_VLOG_NONE, NULL, value, name);
                    goto error;
                }
                *restrs = calloc(1, sizeof **restrs);
                LY_CHECK_ERR_GOTO(!(*restrs), LOGMEM(ctx), error);
                (*restrs)->expr = lydict_insert(ctx, value, 0);


                if (read_restr_substmt(module, *restrs, node, unres)) {
                    goto error;
                }

                for (j = 0; j < (*restrs)->ext_size; ++j) {

                    if ((*restrs)->ext[j]->flags & LYEXT_OPT_VALID) {
                        type->parent->flags |= LYS_VALID_EXT;
                        break;
                    }
                }
            } else {
                LOGVAL(ctx, LYE_INSTMT, LY_VLOG_NONE, NULL, node->name);
                goto error;
            }
        }
        break;

    case LY_TYPE_LEAFREF:

        if (!parenttype && lys_ingrouping(parent)) {

            parenttype = 1;
        }


        LY_TREE_FOR(yin->child, node) {
            if (!strcmp(node->name, "path") && !type->der->type.der) {

            } else if (module->version >= 2 && !strcmp(node->name, "require-instance")) {
                if (type->info.lref.req) {
                    LOGVAL(ctx, LYE_TOOMANY, LY_VLOG_NONE, NULL, node->name, yin->name);
                    goto error;
                }
                GETVAL(ctx, value, node, "value");
                if (!strcmp(value, "true")) {
                    type->info.lref.req = 1;
                } else if (!strcmp(value, "false")) {
                    type->info.lref.req = -1;
                } else {
                    LOGVAL(ctx, LYE_INARG, LY_VLOG_NONE, NULL, value, node->name);
                    goto error;
                }


                if (lyp_yin_parse_subnode_ext(module, type, LYEXT_PAR_TYPE, node, LYEXT_SUBSTMT_REQINSTANCE, 0, unres)) {
                    goto error;
                }
            } else {
                LOGVAL(ctx, LYE_INSTMT, LY_VLOG_NONE, NULL, node->name);
                goto error;
            }
        }


        LY_TREE_FOR(yin->child, node) {
            if (!strcmp(node->name, "path") && !type->der->type.der) {
                if (type->info.lref.path) {
                    LOGVAL(ctx, LYE_TOOMANY, LY_VLOG_NONE, NULL, node->name, yin->name);
                    goto error;
                }

                GETVAL(ctx, value, node, "value");

                type->info.lref.path = transform_schema2json(module, value);
                if (!type->info.lref.path) {
                    goto error;
                }


                if (!parenttype && unres_schema_add_node(module, unres, type, UNRES_TYPE_LEAFREF, parent) == -1) {
                    goto error;
                }


                if (lyp_yin_parse_subnode_ext(module, type, LYEXT_PAR_TYPE, node, LYEXT_SUBSTMT_PATH, 0, unres)) {
                    goto error;
                }

                break;
            }
        }

        if (!type->info.lref.path) {
            if (!type->der->type.der) {
                LOGVAL(ctx, LYE_MISSCHILDSTMT, LY_VLOG_NONE, NULL, "path", "type");
                goto error;
            } else {

                type->info.lref.path = lydict_insert(ctx, type->der->type.info.lref.path, 0);
                if (!type->info.lref.req) {
                    type->info.lref.req = type->der->type.info.lref.req;
                }

                if (!parenttype && unres_schema_add_node(module, unres, type, UNRES_TYPE_LEAFREF, parent) == -1) {
                    goto error;
                }
            }
        }

        break;

    case LY_TYPE_STRING:


        i = 0;
        LY_TREE_FOR_SAFE(yin->child, next, node) {

            if (!strcmp(node->name, "length")) {
                if (type->info.str.length) {
                    LOGVAL(ctx, LYE_TOOMANY, LY_VLOG_NONE, NULL, node->name, yin->name);
                    goto error;
                }

                GETVAL(ctx, value, node, "value");
                if (lyp_check_length_range(ctx, value, type)) {
                    LOGVAL(ctx, LYE_INARG, LY_VLOG_NONE, NULL, value, "length");
                    goto error;
                }
                type->info.str.length = calloc(1, sizeof *type->info.str.length);
                LY_CHECK_ERR_GOTO(!type->info.str.length, LOGMEM(ctx), error);
                type->info.str.length->expr = lydict_insert(ctx, value, 0);


                if (read_restr_substmt(module, type->info.str.length, node, unres)) {
                    goto error;
                }

                for (j = 0; j < type->info.str.length->ext_size; ++j) {

                    if (type->info.str.length->ext[j]->flags & LYEXT_OPT_VALID) {
                        type->parent->flags |= LYS_VALID_EXT;
                        break;
                    }
                }
                lyxml_free(ctx, node);
            } else if (!strcmp(node->name, "pattern")) {
                YIN_CHECK_ARRAY_OVERFLOW_GOTO(ctx, i, type->info.str.pat_count, "patterns", "type", error);
                i++;
            } else {
                LOGVAL(ctx, LYE_INSTMT, LY_VLOG_NONE, NULL, node->name);
                goto error;
            }
        }

        if (i) {
            if (!parenttype && parent && lys_ingrouping(parent)) {
                in_grp = 1;
            }
            type->info.str.patterns = calloc(i, sizeof *type->info.str.patterns);
            LY_CHECK_ERR_GOTO(!type->info.str.patterns, LOGMEM(ctx), error);
#ifdef LY_ENABLED_CACHE
            if (!in_grp) {

                type->info.str.patterns_pcre = calloc(2 * i, sizeof *type->info.str.patterns_pcre);
                LY_CHECK_ERR_GOTO(!type->info.str.patterns_pcre, LOGMEM(ctx), error);
            }
#endif
            LY_TREE_FOR(yin->child, node) {
                GETVAL(ctx, value, node, "value");

                if (in_grp) {

                    if (!(ctx->models.flags & LY_CTX_TRUSTED) && lyp_check_pattern(ctx, value, NULL)) {
                        goto error;
                    }
                }
#ifdef LY_ENABLED_CACHE
                else {

                    if (lyp_precompile_pattern(ctx, value,
                            (pcre **)&type->info.str.patterns_pcre[type->info.str.pat_count * 2],
                            (pcre_extra **)&type->info.str.patterns_pcre[type->info.str.pat_count * 2 + 1])) {
                        goto error;
                    }
                }
#endif
                restr = &type->info.str.patterns[type->info.str.pat_count];
                type->info.str.pat_count++;

                modifier = 0x06;
                name = NULL;
                if (module->version >= 2) {
                    LY_TREE_FOR_SAFE(node->child, next2, child) {
                        if (child->ns && !strcmp(child->ns->value, LY_NSYIN) && !strcmp(child->name, "modifier")) {
                            if (name) {
                                LOGVAL(ctx, LYE_TOOMANY, LY_VLOG_NONE, NULL, "modifier", node->name);
                                goto error;
                            }

                            GETVAL(ctx, name, child, "value");
                            if (!strcmp(name, "invert-match")) {
                                modifier = 0x15;
                            } else {
                                LOGVAL(ctx, LYE_INARG, LY_VLOG_NONE, NULL, name, "modifier");
                                goto error;
                            }

                            if (lyp_yin_parse_subnode_ext(module, restr, LYEXT_PAR_RESTR, child,
                                                          LYEXT_SUBSTMT_MODIFIER, 0, unres)) {
                                goto error;
                            }

                            lyxml_free(ctx, child);
                        }
                    }
                }

                len = strlen(value);
                buf = malloc((len + 2) * sizeof *buf);
                LY_CHECK_ERR_GOTO(!buf, LOGMEM(ctx), error);
                buf[0] = modifier;
                strcpy(&buf[1], value);

                restr->expr = lydict_insert_zc(ctx, buf);


                if (read_restr_substmt(module, restr, node, unres)) {
                    goto error;
                }

                for (j = 0; j < restr->ext_size; ++j) {

                    if (restr->ext[j]->flags & LYEXT_OPT_VALID) {
                        type->parent->flags |= LYS_VALID_EXT;
                        break;
                    }
                }
            }
        }
        break;

    case LY_TYPE_UNION:


        i = 0;
        LY_TREE_FOR_SAFE(yin->child, next, node) {

            if (!strcmp(node->name, "type")) {
                if (type->der->type.der) {

                    LOGVAL(ctx, LYE_INCHILDSTMT, LY_VLOG_NONE, NULL, "type", "derived type");
                    goto error;
                }
                YIN_CHECK_ARRAY_OVERFLOW_GOTO(ctx, i, type->info.uni.count, "types", "type", error);
                i++;
            } else {
                LOGVAL(ctx, LYE_INSTMT, LY_VLOG_NONE, NULL, node->name);
                goto error;
            }
        }

        if (!i && !type->der->type.der) {
            LOGVAL(ctx, LYE_MISSCHILDSTMT, LY_VLOG_NONE, NULL, "type", "(union) type");
            goto error;
        }


        if ((type->der->type.base == LY_TYPE_UNION) && type->der->type.info.uni.has_ptr_type) {
            type->info.uni.has_ptr_type = 1;
        }


        if (i) {
            type->info.uni.types = calloc(i, sizeof *type->info.uni.types);
            LY_CHECK_ERR_GOTO(!type->info.uni.types, LOGMEM(ctx), error);
        }


        LY_TREE_FOR(yin->child, node) {
            type->info.uni.types[type->info.uni.count].parent = type->parent;
            rc = fill_yin_type(module, parent, node, &type->info.uni.types[type->info.uni.count], parenttype, unres);
            if (!rc) {
                type->info.uni.count++;

                if (module->version < 2) {

                    if (type->info.uni.types[type->info.uni.count - 1].base == LY_TYPE_EMPTY) {
                        LOGVAL(ctx, LYE_INARG, LY_VLOG_NONE, NULL, "empty", node->name);
                        rc = -1;
                    } else if (type->info.uni.types[type->info.uni.count - 1].base == LY_TYPE_LEAFREF) {
                        LOGVAL(ctx, LYE_INARG, LY_VLOG_NONE, NULL, "leafref", node->name);
                        rc = -1;
                    }
                }

                if ((type->info.uni.types[type->info.uni.count - 1].base == LY_TYPE_INST)
                        || (type->info.uni.types[type->info.uni.count - 1].base == LY_TYPE_LEAFREF)
                        || ((type->info.uni.types[type->info.uni.count - 1].base == LY_TYPE_UNION)
                        && type->info.uni.types[type->info.uni.count - 1].info.uni.has_ptr_type)) {
                    type->info.uni.has_ptr_type = 1;
                }
            }
            if (rc) {

                for (i = 0; i < type->info.uni.count; ++i) {
                    lys_type_free(ctx, &type->info.uni.types[i], NULL);
                }
                free(type->info.uni.types);
                type->info.uni.types = NULL;
                type->info.uni.count = 0;
                type->info.uni.has_ptr_type = 0;
                type->der = NULL;
                type->base = LY_TYPE_DER;

                if (rc == EXIT_FAILURE) {
                    ret = EXIT_FAILURE;
                }
                goto error;
            }
        }
        break;

    case LY_TYPE_BOOL:
    case LY_TYPE_EMPTY:

        if (yin->child) {
            LOGVAL(ctx, LYE_INSTMT, LY_VLOG_NONE, NULL, yin->child->name);
            goto error;
        }
        break;

    default:
        LOGINT(ctx);
        goto error;
    }

    for(j = 0; j < type->ext_size; ++j) {

        if (type->ext[j]->flags & LYEXT_OPT_VALID) {
            type->parent->flags |= LYS_VALID_EXT;
            break;
        }
    }


    dertype = &type->der->type;
    while (dertype->der) {
        if (dertype->parent->flags & LYS_VALID_EXT) {
            type->parent->flags |= LYS_VALID_EXT;
        }
        dertype = &dertype->der->type;
    }

    return EXIT_SUCCESS;

error:
    lyxml_free_withsiblings(ctx, exts.child);
    return ret;
}
