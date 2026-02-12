lyp_parse_value(struct lys_type *type, const char **value_, struct lyxml_elem *xml,
                struct lyd_node_leaf_list *leaf, struct lyd_attr *attr, struct lys_module *local_mod,
                int store, int dflt, int trusted)
{
    struct lys_type *ret = NULL, *t;
    struct lys_tpdf *tpdf;
    enum int_log_opts prev_ilo;
    int c, len, found = 0;
    unsigned int i, j;
    int64_t num;
    uint64_t unum, uind, u = 0;
    const char *ptr, *value = *value_, *itemname, *old_val_str = NULL;
    struct lys_type_bit **bits = NULL;
    struct lys_ident *ident;
    lyd_val *val, old_val;
    LY_DATA_TYPE *val_type, old_val_type;
    uint8_t *val_flags, old_val_flags;
    struct lyd_node *contextnode;
    struct ly_ctx *ctx = type->parent->module->ctx;

    assert(leaf || attr);

    if (leaf) {
        assert(!attr);
        if (!local_mod) {
            local_mod = leaf->schema->module;
        }
        val = &leaf->value;
        val_type = &leaf->value_type;
        val_flags = &leaf->value_flags;
        contextnode = (struct lyd_node *)leaf;
        itemname = leaf->schema->name;
    } else {
        assert(!leaf);
        if (!local_mod) {
            local_mod = attr->annotation->module;
        }
        val = &attr->value;
        val_type = &attr->value_type;
        val_flags = &attr->value_flags;
        contextnode = attr->parent;
        itemname = attr->name;
    }


    if (store) {
        old_val_str = lydict_insert(ctx, *value_, 0);
        lyd_free_value(*val, *val_type, *val_flags, type, old_val_str, &old_val, &old_val_type, &old_val_flags);
        *val_flags &= ~LY_VALUE_UNRES;
    }

    switch (type->base) {
    case LY_TYPE_BINARY:

        unum = 0;
        ptr = NULL;
        if (value) {

            for (uind = 0; isspace(value[uind]); ++uind);
            ptr = &value[uind];
            u = strlen(ptr);
            while (u && isspace(ptr[u - 1])) {
                --u;
            }
            unum = u;
            for (uind = 0; uind < u; ++uind) {
                if (ptr[uind] == '\n') {
                    unum--;
                } else if ((ptr[uind] < '/' && ptr[uind] != '+') ||
                    (ptr[uind] > '9' && ptr[uind] < 'A') ||
                    (ptr[uind] > 'Z' && ptr[uind] < 'a') || ptr[uind] > 'z') {
                    if (ptr[uind] == '=') {

                        if (uind == u - 2 && ptr[uind + 1] == '=') {
                            found = 2;
                            uind++;
                        } else if (uind == u - 1) {
                            found = 1;
                        }
                    }
                    if (!found) {

                        LOGVAL(ctx, LYE_INCHAR, LY_VLOG_LYD, contextnode, ptr[uind], &ptr[uind]);
                        LOGVAL(ctx, LYE_SPEC, LY_VLOG_PREV, NULL, "Invalid Base64 character.");
                        goto error;
                    }
                }
            }
        }

        if (unum & 3) {

            if (leaf) {
                LOGVAL(ctx, LYE_INVAL, LY_VLOG_LYD, contextnode, value, itemname);
            } else {
                LOGVAL(ctx, LYE_INMETA, LY_VLOG_LYD, contextnode, "<none>", itemname, value);
            }
            LOGVAL(ctx, LYE_SPEC, LY_VLOG_PREV, NULL, "Base64 encoded value length must be divisible by 4.");
            goto error;
        }


        len = ((unum / 4) * 3) - found;
        if (!trusted && validate_length_range(0, len, 0, 0, 0, type, value, contextnode)) {
            goto error;
        }

        if (value && (ptr != value || ptr[u] != '\0')) {

            ptr = lydict_insert(ctx, ptr, u);
            lydict_remove(ctx, *value_);
            *value_ = ptr;
        }

        if (store) {

            val->binary = value;
            *val_type = LY_TYPE_BINARY;
        }
        break;

    case LY_TYPE_BITS:


        for (; !type->info.bits.count; type = &type->der->type);

        if (value || store) {

            bits = calloc(type->info.bits.count, sizeof *bits);
            LY_CHECK_ERR_GOTO(!bits, LOGMEM(ctx), error);
        }

        if (!value) {

            if (store) {

                val->bit = bits;
                *val_type = LY_TYPE_BITS;
            }
            break;
        }

        c = 0;
        i = 0;
        while (value[c]) {

            while (isspace(value[c])) {
                c++;
            }
            if (!value[c]) {

                break;
            }


            for (len = 0; value[c] && !isspace(value[c]); c++, len++);


            c = c - len;


            for (found = i = 0; i < type->info.bits.count; i++) {
                if (!strncmp(type->info.bits.bit[i].name, &value[c], len) && !type->info.bits.bit[i].name[len]) {

                    for (j = 0; !trusted && (j < type->info.bits.bit[i].iffeature_size); j++) {
                        if (!resolve_iffeature(&type->info.bits.bit[i].iffeature[j])) {
                            if (leaf) {
                                LOGVAL(ctx, LYE_INVAL, LY_VLOG_LYD, contextnode, value, itemname);
                            } else {
                                LOGVAL(ctx, LYE_INMETA, LY_VLOG_LYD, contextnode, "<none>", itemname, value);
                            }
                            LOGVAL(ctx, LYE_SPEC, LY_VLOG_PREV, NULL,
                                   "Bit \"%s\" is disabled by its %d. if-feature condition.",
                                   type->info.bits.bit[i].name, j + 1);
                            free(bits);
                            goto error;
                        }
                    }

                    if (bits[i]) {
                        if (leaf) {
                            LOGVAL(ctx, LYE_INVAL, LY_VLOG_LYD, contextnode, value, itemname);
                        } else {
                            LOGVAL(ctx, LYE_INMETA, LY_VLOG_LYD, contextnode, "<none>", itemname, value);
                        }
                        LOGVAL(ctx, LYE_SPEC, LY_VLOG_PREV, NULL, "Bit \"%s\" used multiple times.",
                               type->info.bits.bit[i].name);
                        free(bits);
                        goto error;
                    }

                    bits[i] = &type->info.bits.bit[i];


                    found = 1;
                    break;
                }
            }

            if (!found) {

                if (leaf) {
                    LOGVAL(ctx, LYE_INVAL, LY_VLOG_LYD, contextnode, value, itemname);
                } else {
                    LOGVAL(ctx, LYE_INMETA, LY_VLOG_LYD, contextnode, "<none>", itemname, value);
                }
                free(bits);
                goto error;
            }
            c = c + len;
        }

        if (make_canonical(ctx, LY_TYPE_BITS, value_, bits, &type->info.bits.count) == -1) {
            free(bits);
            goto error;
        }

        if (store) {

            val->bit = bits;
            *val_type = LY_TYPE_BITS;
        } else {
            free(bits);
        }
        break;

    case LY_TYPE_BOOL:
        if (value && !strcmp(value, "true")) {
            if (store) {
                val->bln = 1;
            }
        } else if (!value || strcmp(value, "false")) {
            if (leaf) {
                LOGVAL(ctx, LYE_INVAL, LY_VLOG_LYD, contextnode, value ? value : "", itemname);
            } else {
                LOGVAL(ctx, LYE_INMETA, LY_VLOG_LYD, contextnode, "<none>", itemname, value ? value : "");
            }
            goto error;
        } else {
            if (store) {
                val->bln = 0;
            }
        }

        if (store) {
            *val_type = LY_TYPE_BOOL;
        }
        break;

    case LY_TYPE_DEC64:
        if (!value || !value[0]) {
            if (leaf) {
                LOGVAL(ctx, LYE_INVAL, LY_VLOG_LYD, contextnode, "", itemname);
            } else {
                LOGVAL(ctx, LYE_INMETA, LY_VLOG_LYD, contextnode, "<none>", itemname, "");
            }
            goto error;
        }

        ptr = value;
        if (parse_range_dec64(&ptr, type->info.dec64.dig, &num) || ptr[0]) {
            if (leaf) {
                LOGVAL(ctx, LYE_INVAL, LY_VLOG_LYD, contextnode, value, itemname);
            } else {
                LOGVAL(ctx, LYE_INMETA, LY_VLOG_LYD, contextnode, "<none>", itemname, value);
            }
            goto error;
        }

        if (!trusted && validate_length_range(2, 0, 0, num, type->info.dec64.dig, type, value, contextnode)) {
            goto error;
        }

        if (make_canonical(ctx, LY_TYPE_DEC64, value_, &num, &type->info.dec64.dig) == -1) {
            goto error;
        }

        if (store) {

            val->dec64 = num;
            *val_type = LY_TYPE_DEC64;
        }
        break;

    case LY_TYPE_EMPTY:
        if (value && value[0]) {
            if (leaf) {
                LOGVAL(ctx, LYE_INVAL, LY_VLOG_LYD, contextnode, value, itemname);
            } else {
                LOGVAL(ctx, LYE_INMETA, LY_VLOG_LYD, contextnode, "<none>", itemname, value);
            }
            goto error;
        }

        if (store) {
            *val_type = LY_TYPE_EMPTY;
        }
        break;

    case LY_TYPE_ENUM:


        for (; !type->info.enums.count; type = &type->der->type);


        for (i = found = 0; i < type->info.enums.count; i++) {
            if (value && !strcmp(value, type->info.enums.enm[i].name)) {

                for (j = 0; !trusted && (j < type->info.enums.enm[i].iffeature_size); j++) {
                    if (!resolve_iffeature(&type->info.enums.enm[i].iffeature[j])) {
                        if (leaf) {
                            LOGVAL(ctx, LYE_INVAL, LY_VLOG_LYD, contextnode, value, itemname);
                        } else {
                            LOGVAL(ctx, LYE_INMETA, LY_VLOG_LYD, contextnode, "<none>", itemname, value);
                        }
                        LOGVAL(ctx, LYE_SPEC, LY_VLOG_PREV, NULL, "Enum \"%s\" is disabled by its %d. if-feature condition.",
                               value, j + 1);
                        goto error;
                    }
                }

                if (store) {
                    val->enm = &type->info.enums.enm[i];
                    *val_type = LY_TYPE_ENUM;
                }
                found = 1;
                break;
            }
        }

        if (!found) {
            if (leaf) {
                LOGVAL(ctx, LYE_INVAL, LY_VLOG_LYD, contextnode, value ? value : "", itemname);
            } else {
                LOGVAL(ctx, LYE_INMETA, LY_VLOG_LYD, contextnode, "<none>", itemname, value ? value : "");
            }
            goto error;
        }
        break;

    case LY_TYPE_IDENT:
        if (!value) {
            if (leaf) {
                LOGVAL(ctx, LYE_INVAL, LY_VLOG_LYD, contextnode, "", itemname);
            } else {
                LOGVAL(ctx, LYE_INMETA, LY_VLOG_LYD, contextnode, "<none>", itemname, "");
            }
            goto error;
        }

        if (xml) {
            ly_ilo_change(NULL, ILO_IGNORE, &prev_ilo, NULL);

            value = transform_xml2json(ctx, value, xml, 0, 0);
            ly_ilo_restore(NULL, prev_ilo, NULL, 0);
            if (!value) {

                if (leaf) {
                    LOGVAL(ctx, LYE_INVAL, LY_VLOG_LYD, contextnode, *value_, itemname);
                } else {
                    LOGVAL(ctx, LYE_INMETA, LY_VLOG_LYD, contextnode, "<none>", itemname, *value_);
                }
                goto error;
            }


            if (!strchr(value, ':') && xml->ns->prefix) {
                value = ident_val_add_module_prefix(value, xml, ctx);
                if (!value) {
                    goto error;
                }
            }
        } else if (dflt) {
            ly_ilo_change(NULL, ILO_IGNORE, &prev_ilo, NULL);


            value = transform_schema2json(local_mod, value);
            ly_ilo_restore(NULL, prev_ilo, NULL, 0);
            if (!value) {

                value = lydict_insert(ctx, *value_, 0);
            }
        } else {
            value = lydict_insert(ctx, *value_, 0);
        }


        ident = resolve_identref(type, value, contextnode, local_mod, dflt);
        if (!ident) {
            lydict_remove(ctx, value);
            goto error;
        } else if (store) {

            val->ident = ident;
            *val_type = LY_TYPE_IDENT;
        }


        if (dflt) {
            type->parent->flags |= LYS_DFLTJSON;
        }

        if (make_canonical(ctx, LY_TYPE_IDENT, &value, (void*)lys_main_module(local_mod)->name, NULL) == -1) {
            lydict_remove(ctx, value);
            goto error;
        }


        lydict_remove(ctx, *value_);
        *value_ = value;
        break;

    case LY_TYPE_INST:
        if (!value) {
            if (leaf) {
                LOGVAL(ctx, LYE_INVAL, LY_VLOG_LYD, contextnode, "", itemname);
            } else {
                LOGVAL(ctx, LYE_INMETA, LY_VLOG_LYD, contextnode, "<none>", itemname, "");
            }
            goto error;
        }

        if (xml) {
            ly_ilo_change(NULL, ILO_IGNORE, &prev_ilo, NULL);

            value = transform_xml2json(ctx, value, xml, 1, 1);
            ly_ilo_restore(NULL, prev_ilo, NULL, 0);
            if (!value) {

                if (leaf) {
                    LOGVAL(ctx, LYE_INVAL, LY_VLOG_LYD, contextnode, *value_, itemname);
                } else {
                    LOGVAL(ctx, LYE_INMETA, LY_VLOG_LYD, contextnode, "<none>", itemname, *value_);
                }
                goto error;
            } else if (ly_strequal(value, *value_, 1)) {


                lydict_remove(ctx, value);
            }
        } else if (dflt) {

            ly_ilo_change(NULL, ILO_IGNORE, &prev_ilo, NULL);


            value = transform_schema2json(local_mod, value);
            if (!value) {

                value = *value_;
            } else if (ly_strequal(value, *value_, 1)) {


                lydict_remove(ctx, value);
            }

            ly_ilo_restore(NULL, prev_ilo, NULL, 0);
        } else {
            if ((c = make_canonical(ctx, LY_TYPE_INST, &value, NULL, NULL))) {
                if (c == -1) {
                    goto error;
                }


                *value_ = value;
            }
        }

        if (store) {

            val->instance = NULL;
            *val_type = LY_TYPE_INST;
            *val_flags |= LY_VALUE_UNRES;
        }

        if (!ly_strequal(value, *value_, 1)) {

            lydict_remove(ctx, *value_);
            *value_ = value;


            if (dflt) {
                type->parent->flags |= LYS_DFLTJSON;
            }
        }
        break;

    case LY_TYPE_LEAFREF:
        if (!value) {
            if (leaf) {
                LOGVAL(ctx, LYE_INVAL, LY_VLOG_LYD, contextnode, "", itemname);
            } else {
                LOGVAL(ctx, LYE_INMETA, LY_VLOG_LYD, contextnode, "<none>", itemname, "");
            }
            goto error;
        }


        t = lyp_parse_value(&type->info.lref.target->type, value_, xml, leaf, attr, NULL, store, dflt, trusted);
        value = *value_;
        if (!t) {

            goto error;
        }

        if (store) {

            *val_flags |= LY_VALUE_UNRES;
        }

        type = t;
        break;

    case LY_TYPE_STRING:
        if (!trusted && validate_length_range(0, (value ? ly_strlen_utf8(value) : 0), 0, 0, 0, type, value, contextnode)) {
            goto error;
        }

        if (!trusted && validate_pattern(ctx, value, type, contextnode)) {
            goto error;
        }


        for (tpdf = type->der;
             tpdf->module && (strcmp(tpdf->name, "xpath1.0") || strcmp(tpdf->module->name, "ietf-yang-types"));
             tpdf = tpdf->type.der);
        if (tpdf->module && xml) {

            value = transform_xml2json(ctx, value ? value : "", xml, 1, 1);
            if (!value) {

                if (leaf) {
                    LOGVAL(ctx, LYE_INVAL, LY_VLOG_LYD, contextnode, *value_, itemname);
                } else {
                    LOGVAL(ctx, LYE_INMETA, LY_VLOG_LYD, contextnode, "<none>", itemname, *value_);
                }
                goto error;
            }

            if (!ly_strequal(value, *value_, 1)) {

                lydict_remove(ctx, *value_);
                *value_ = value;
            }
        }

        if (store) {

            val->string = value;
            *val_type = LY_TYPE_STRING;
        }
        break;

    case LY_TYPE_INT8:
        if (parse_int(value, __INT64_C(-128), __INT64_C(127), dflt ? 0 : 10, &num, contextnode)
                || (!trusted && validate_length_range(1, 0, num, 0, 0, type, value, contextnode))) {
            goto error;
        }

        if (make_canonical(ctx, LY_TYPE_INT8, value_, &num, NULL) == -1) {
            goto error;
        }

        if (store) {

            val->int8 = (int8_t)num;
            *val_type = LY_TYPE_INT8;
        }
        break;

    case LY_TYPE_INT16:
        if (parse_int(value, __INT64_C(-32768), __INT64_C(32767), dflt ? 0 : 10, &num, contextnode)
                || (!trusted && validate_length_range(1, 0, num, 0, 0, type, value, contextnode))) {
            goto error;
        }

        if (make_canonical(ctx, LY_TYPE_INT16, value_, &num, NULL) == -1) {
            goto error;
        }

        if (store) {

            val->int16 = (int16_t)num;
            *val_type = LY_TYPE_INT16;
        }
        break;

    case LY_TYPE_INT32:
        if (parse_int(value, __INT64_C(-2147483648), __INT64_C(2147483647), dflt ? 0 : 10, &num, contextnode)
                || (!trusted && validate_length_range(1, 0, num, 0, 0, type, value, contextnode))) {
            goto error;
        }

        if (make_canonical(ctx, LY_TYPE_INT32, value_, &num, NULL) == -1) {
            goto error;
        }

        if (store) {

            val->int32 = (int32_t)num;
            *val_type = LY_TYPE_INT32;
        }
        break;

    case LY_TYPE_INT64:
        if (parse_int(value, __INT64_C(-9223372036854775807) - __INT64_C(1), __INT64_C(9223372036854775807),
                      dflt ? 0 : 10, &num, contextnode)
                || (!trusted && validate_length_range(1, 0, num, 0, 0, type, value, contextnode))) {
            goto error;
        }

        if (make_canonical(ctx, LY_TYPE_INT64, value_, &num, NULL) == -1) {
            goto error;
        }

        if (store) {

            val->int64 = num;
            *val_type = LY_TYPE_INT64;
        }
        break;

    case LY_TYPE_UINT8:
        if (parse_uint(value, __UINT64_C(255), dflt ? 0 : 10, &unum, contextnode)
                || (!trusted && validate_length_range(0, unum, 0, 0, 0, type, value, contextnode))) {
            goto error;
        }

        if (make_canonical(ctx, LY_TYPE_UINT8, value_, &unum, NULL) == -1) {
            goto error;
        }

        if (store) {

            val->uint8 = (uint8_t)unum;
            *val_type = LY_TYPE_UINT8;
        }
        break;

    case LY_TYPE_UINT16:
        if (parse_uint(value, __UINT64_C(65535), dflt ? 0 : 10, &unum, contextnode)
                || (!trusted && validate_length_range(0, unum, 0, 0, 0, type, value, contextnode))) {
            goto error;
        }

        if (make_canonical(ctx, LY_TYPE_UINT16, value_, &unum, NULL) == -1) {
            goto error;
        }

        if (store) {

            val->uint16 = (uint16_t)unum;
            *val_type = LY_TYPE_UINT16;
        }
        break;

    case LY_TYPE_UINT32:
        if (parse_uint(value, __UINT64_C(4294967295), dflt ? 0 : 10, &unum, contextnode)
                || (!trusted && validate_length_range(0, unum, 0, 0, 0, type, value, contextnode))) {
            goto error;
        }

        if (make_canonical(ctx, LY_TYPE_UINT32, value_, &unum, NULL) == -1) {
            goto error;
        }

        if (store) {

            val->uint32 = (uint32_t)unum;
            *val_type = LY_TYPE_UINT32;
        }
        break;

    case LY_TYPE_UINT64:
        if (parse_uint(value, __UINT64_C(18446744073709551615), dflt ? 0 : 10, &unum, contextnode)
                || (!trusted && validate_length_range(0, unum, 0, 0, 0, type, value, contextnode))) {
            goto error;
        }

        if (make_canonical(ctx, LY_TYPE_UINT64, value_, &unum, NULL) == -1) {
            goto error;
        }

        if (store) {

            val->uint64 = unum;
            *val_type = LY_TYPE_UINT64;
        }
        break;

    case LY_TYPE_UNION:
        if (store) {

            memset(val, 0, sizeof(lyd_val));
            *val_type = LY_TYPE_UNION;
        }

        if (type->info.uni.has_ptr_type) {


            if (xml) {

                ly_ilo_change(NULL, ILO_IGNORE, &prev_ilo, NULL);
                val->string = transform_xml2json(ctx, value, xml, 1, 1);
                ly_ilo_restore(NULL, prev_ilo, NULL, 0);
                if (!val->string) {

                    val->string = lydict_insert(ctx, value, 0);
                }
            }
            break;
        }

        t = NULL;
        found = 0;


        ly_ilo_change(NULL, ILO_IGNORE, &prev_ilo, NULL);

        while ((t = lyp_get_next_union_type(type, t, &found))) {
            found = 0;
            ret = lyp_parse_value(t, value_, xml, leaf, attr, NULL, store, dflt, 0);
            if (ret) {

                type = ret;
                break;
            }

            if (store) {

                lyd_free_value(*val, *val_type, *val_flags, t, *value_, NULL, NULL, NULL);
                memset(val, 0, sizeof(lyd_val));
            }
        }


        ly_ilo_restore(NULL, prev_ilo, NULL, 0);

        if (!t) {

            if (store) {
                *val_type = 0;
            }
            if (leaf) {
                LOGVAL(ctx, LYE_INVAL, LY_VLOG_LYD, contextnode, *value_ ? *value_ : "", itemname);
            } else {
                LOGVAL(ctx, LYE_INMETA, LY_VLOG_LYD, contextnode, "<none>", itemname, *value_);
            }
            goto error;
        }
        break;

    default:
        LOGINT(ctx);
        goto error;
    }


    if (store && type->der && type->der->module) {
        c = lytype_store(type->der->module, type->der->name, value_, val);
        if (c == -1) {
            goto error;
        } else if (!c) {
            *val_flags |= LY_VALUE_USER;
        }
    }


    if (store) {
        lyd_free_value(old_val, old_val_type, old_val_flags, type, old_val_str, NULL, NULL, NULL);
        lydict_remove(ctx, old_val_str);
    }
    return type;

error:

    if (store) {
        *val = old_val;
        *val_type = old_val_type;
        *val_flags = old_val_flags;
        lydict_remove(ctx, old_val_str);
    }
    return NULL;
}
