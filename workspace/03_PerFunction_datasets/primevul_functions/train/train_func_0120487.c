unres_schema_add_node(struct lys_module *mod, struct unres_schema *unres, void *item, enum UNRES_ITEM type,
                      struct lys_node *snode)
{
    int rc;
    uint32_t u;
    enum int_log_opts prev_ilo;
    struct ly_err_item *prev_eitem;
    LY_ERR prev_ly_errno;
    struct lyxml_elem *yin;
    struct ly_ctx *ctx = mod->ctx;

    assert(unres && (item || (type == UNRES_MOD_IMPLEMENT)) && ((type != UNRES_LEAFREF) && (type != UNRES_INSTID)
           && (type != UNRES_WHEN) && (type != UNRES_MUST)));


    for (u = 0; u < unres->count; u++) {
        if (unres->type[u] == type && unres->item[u] == item &&
                unres->str_snode[u] == snode && unres->module[u] == mod) {


            return EXIT_FAILURE;
        }
    }

    if ((type == UNRES_EXT_FINALIZE) || (type == UNRES_XPATH) || (type == UNRES_MOD_IMPLEMENT)) {


        rc = EXIT_FAILURE;
    } else {
        prev_ly_errno = ly_errno;
        ly_ilo_change(ctx, ILO_STORE, &prev_ilo, &prev_eitem);

        rc = resolve_unres_schema_item(mod, item, type, snode, unres);
        if (rc != EXIT_FAILURE) {
            ly_ilo_restore(ctx, prev_ilo, prev_eitem, rc == -1 ? 1 : 0);
            if (rc != -1) {
                ly_errno = prev_ly_errno;
            }

            if (type == UNRES_LIST_UNIQ) {

                free(item);
            } else if (rc == -1 && type == UNRES_IFFEAT) {

                free(*((char **)item));
            }
            return rc;
        } else {

            ly_ilo_restore(ctx, prev_ilo, prev_eitem, 0);
            ly_errno = prev_ly_errno;
        }

        print_unres_schema_item_fail(item, type, snode);


        if (type == UNRES_TYPE_DER || type == UNRES_TYPE_DER_TPDF) {
            yin = (struct lyxml_elem *)((struct lys_type *)item)->der;
            if (!(yin->flags & LY_YANG_STRUCTURE_FLAG)) {
                lyxml_unlink_elem(mod->ctx, yin, 1);
                ((struct lys_type *)item)->der = (struct lys_tpdf *)yin;
            }
        }
    }

    unres->count++;
    unres->item = ly_realloc(unres->item, unres->count*sizeof *unres->item);
    LY_CHECK_ERR_RETURN(!unres->item, LOGMEM(ctx), -1);
    unres->item[unres->count-1] = item;
    unres->type = ly_realloc(unres->type, unres->count*sizeof *unres->type);
    LY_CHECK_ERR_RETURN(!unres->type, LOGMEM(ctx), -1);
    unres->type[unres->count-1] = type;
    unres->str_snode = ly_realloc(unres->str_snode, unres->count*sizeof *unres->str_snode);
    LY_CHECK_ERR_RETURN(!unres->str_snode, LOGMEM(ctx), -1);
    unres->str_snode[unres->count-1] = snode;
    unres->module = ly_realloc(unres->module, unres->count*sizeof *unres->module);
    LY_CHECK_ERR_RETURN(!unres->module, LOGMEM(ctx), -1);
    unres->module[unres->count-1] = mod;

    return rc;
}
