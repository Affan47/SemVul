lyp_check_include_missing(struct lys_module *main_module)
{
    int ret = 0;
    uint8_t i;


    for (i = 0; i < main_module->inc_size; i++) {
        if (lyp_check_include_missing_recursive(main_module, main_module->inc[i].submodule)) {
            ret = 1;
        }
    }

    return ret;
}
