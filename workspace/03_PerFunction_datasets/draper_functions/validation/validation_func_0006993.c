process(ast_procdef *p) {
    cpp_opt_common_nbr_t T;
    gm_traverse_sents(p->get_body(), &T);
    if (T.has_targets()) {
        T.transform_targets();
        set_affected(true);
    }
}
