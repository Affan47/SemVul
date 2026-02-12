yang_fill_unique(struct lys_module *module, struct lys_node_list *list, struct lys_unique *unique, char *value, struct unres_schema *unres)
{
    int i, j;
    char *vaux, c;
    struct unres_list_uniq *unique_info;


    vaux = value;
    while ((vaux = strpbrk(vaux, " \t\n"))) {
       unique->expr_size++;
        while (isspace(*vaux)) {
            vaux++;
        }
    }
    unique->expr_size++;
    unique->expr = calloc(unique->expr_size, sizeof *unique->expr);
    LY_CHECK_ERR_GOTO(!unique->expr, LOGMEM(module->ctx), error);

    for (i = 0; i < unique->expr_size; i++) {
        vaux = strpbrk(value, " \t\n");
        if (vaux) {
            c = *vaux;
            *vaux = '\0';
        }


        unique->expr[i] = transform_schema2json(module, value);
        if (!unique->expr[i]) {
            LOGVAL(module->ctx, LYE_INARG, LY_VLOG_LYS, list, value, "unique");
            goto error;
        }
        if (vaux) {
            *vaux = c;
        }


        for (j = 0; j < i; j++) {
            if (ly_strequal(unique->expr[j], unique->expr[i], 1)) {
                LOGVAL(module->ctx, LYE_INARG, LY_VLOG_LYS, list, unique->expr[i], "unique");
                LOGVAL(module->ctx, LYE_SPEC, LY_VLOG_LYS, list, "The identifier is not unique");
                goto error;
            }
        }

        if (unres) {
            unique_info = malloc(sizeof *unique_info);
            LY_CHECK_ERR_GOTO(!unique_info, LOGMEM(module->ctx), error);
            unique_info->list = (struct lys_node *)list;
            unique_info->expr = unique->expr[i];
            unique_info->trg_type = &unique->trg_type;
            if (unres_schema_add_node(module, unres, unique_info, UNRES_LIST_UNIQ, NULL) == -1) {
                goto error;
            }
        } else {
            if (resolve_unique((struct lys_node *)list, unique->expr[i], &unique->trg_type)) {
                goto error;
            }
        }


        value = vaux;
        while(value && isspace(*value)) {
            value++;
        }
    }

    return EXIT_SUCCESS;

error:
    return EXIT_FAILURE;
}
