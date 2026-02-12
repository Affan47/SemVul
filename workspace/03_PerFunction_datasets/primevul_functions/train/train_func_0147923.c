lyp_get_import_module_ns(const struct lys_module *module, const char *ns)
{
    int i;
    const struct lys_module *mod = NULL;

    assert(module && ns);

    if (module->type) {

        if (ly_strequal(((struct lys_submodule *)module)->belongsto->ns, ns, 0)) {
            return ((struct lys_submodule *)module)->belongsto;
        }
    } else {

        if (ly_strequal(module->ns, ns, 0)) {
            return module;
        }
    }


    for (i = 0; i < module->imp_size; ++i) {
        if (ly_strequal(module->imp[i].module->ns, ns, 0)) {
            return module->imp[i].module;
        }
    }

    return mod;
}
