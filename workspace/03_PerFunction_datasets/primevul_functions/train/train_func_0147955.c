lyp_mand_check_ext(struct lys_ext_instance_complex *ext, const char *ext_name)
{
    void *p;
    int i;
    struct ly_ctx *ctx = ext->module->ctx;


    for (i = 0; ext->substmt[i].stmt; i++) {
        if (ext->substmt[i].cardinality == LY_STMT_CARD_OPT || ext->substmt[i].cardinality == LY_STMT_CARD_ANY) {

            continue;
        } else if (ext->substmt[i].cardinality == LY_STMT_CARD_SOME) {
            goto array;
        }


        switch(ext->substmt[i].stmt) {
        case LY_STMT_ORDEREDBY:

            break;
        case LY_STMT_REQINSTANCE:
        case LY_STMT_DIGITS:
        case LY_STMT_MODIFIER:
            p = lys_ext_complex_get_substmt(ext->substmt[i].stmt, ext, NULL);
            if (!*(uint8_t*)p) {
                LOGVAL(ctx, LYE_MISSCHILDSTMT, LY_VLOG_NONE, NULL, ly_stmt_str[ext->substmt[i].stmt], ext_name);
                goto error;
            }
            break;
        case LY_STMT_STATUS:
            p = lys_ext_complex_get_substmt(ext->substmt[i].stmt, ext, NULL);
            if (!(*(uint16_t*)p & LYS_STATUS_MASK)) {
                LOGVAL(ctx, LYE_MISSCHILDSTMT, LY_VLOG_NONE, NULL, ly_stmt_str[ext->substmt[i].stmt], ext_name);
                goto error;
            }
            break;
        case LY_STMT_MANDATORY:
            p = lys_ext_complex_get_substmt(ext->substmt[i].stmt, ext, NULL);
            if (!(*(uint16_t*)p & LYS_MAND_MASK)) {
                LOGVAL(ctx, LYE_MISSCHILDSTMT, LY_VLOG_NONE, NULL, ly_stmt_str[ext->substmt[i].stmt], ext_name);
                goto error;
            }
            break;
        case LY_STMT_CONFIG:
            p = lys_ext_complex_get_substmt(ext->substmt[i].stmt, ext, NULL);
            if (!(*(uint16_t*)p & LYS_CONFIG_MASK)) {
                LOGVAL(ctx, LYE_MISSCHILDSTMT, LY_VLOG_NONE, NULL, ly_stmt_str[ext->substmt[i].stmt], ext_name);
                goto error;
            }
            break;
        default:
array:

            p = lys_ext_complex_get_substmt(ext->substmt[i].stmt, ext, NULL);
            if (!(*(void**)p)) {
                LOGVAL(ctx, LYE_MISSCHILDSTMT, LY_VLOG_NONE, NULL, ly_stmt_str[ext->substmt[i].stmt], ext_name);
                goto error;
            }
            break;
        }
    }

    return EXIT_SUCCESS;

error:
    return EXIT_FAILURE;
}
