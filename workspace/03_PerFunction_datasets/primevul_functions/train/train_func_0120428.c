schema_nodeid_siblingcheck(const struct lys_node *sibling, const struct lys_module *cur_module, const char *mod_name,
                           int mod_name_len, const char *name, int nam_len)
{
    const struct lys_module *prefix_mod;


    if (name[0] == '*') {
        return 2;
    } else if (name[0] == '.') {
        return 3;
    }


    if (strncmp(name, sibling->name, nam_len) || sibling->name[nam_len]) {
        return 1;
    }


    if (mod_name) {
        prefix_mod = lyp_get_module(cur_module, NULL, 0, mod_name, mod_name_len, 0);
        if (!prefix_mod) {
            return -1;
        }
    } else {
        prefix_mod = cur_module;
    }
    if (prefix_mod != lys_node_module(sibling)) {
        return 1;
    }


    return 0;
}
