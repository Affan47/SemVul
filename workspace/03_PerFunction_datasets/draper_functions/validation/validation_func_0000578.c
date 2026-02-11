traverse_expr_for_readset_adding_reduce(ast_expr_reduce* e2, gm_rwinfo_map& rset, temp_map_t& DrvMap) {
    gm_symtab_entry *it = e2->get_iterator()->getSymInfo();
    int iter_type = e2->get_iter_type();
    ast_expr* f = e2->get_filter();
    ast_expr* b = e2->get_body();
    bool is_conditional = (f != NULL) || gm_is_collection_iterator_type(iter_type);
    int src_type = get_iteration_src_type_summary(e2->get_iterator());
    range_cond_t R(gm_get_range_from_itertype(iter_type, src_type), !is_conditional);
    DrvMap[it] = R;
    traverse_expr_for_readset_adding(b, rset, DrvMap);
    DrvMap.erase(it);

    if (f != NULL) {
        DrvMap[it] = R;
        R.is_always = true;
        traverse_expr_for_readset_adding(f, rset, DrvMap);
        DrvMap.erase(it);
    }
}
