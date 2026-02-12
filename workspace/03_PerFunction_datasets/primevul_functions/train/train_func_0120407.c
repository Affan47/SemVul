check_instid_ext_dep(const struct lys_node *sleaf, const char *json_instid)
{
    const struct lys_node *op_node, *first_node;
    enum int_log_opts prev_ilo;
    char *buf, *tmp;

    if (!json_instid || !json_instid[0]) {

        return 0;
    }

    for (op_node = lys_parent(sleaf);
         op_node && !(op_node->nodetype & (LYS_NOTIF | LYS_RPC | LYS_ACTION));
         op_node = lys_parent(op_node));

    if (op_node && lys_parent(op_node)) {

        return 1;
    }


    tmp = strchr(json_instid + 1, '/');
    buf = strndup(json_instid, tmp ? (size_t)(tmp - json_instid) : strlen(json_instid));
    if (!buf) {

        return 0;
    }


    ly_ilo_change(NULL, ILO_IGNORE, &prev_ilo, NULL);
    first_node = ly_ctx_get_node(NULL, sleaf, buf, 0);
    ly_ilo_restore(NULL, prev_ilo, NULL, 0);

    free(buf);
    if (!first_node) {

        return 1;
    }


    if (op_node) {
        if (op_node != first_node) {

            return 1;
        }
    } else {
        if (lys_node_module(sleaf) != lys_node_module(first_node)) {

            return 1;
        }
    }

    return 0;
}
