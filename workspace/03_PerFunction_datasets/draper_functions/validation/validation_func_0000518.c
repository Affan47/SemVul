rename_array_entry_block(Block *b, const int level)
{
    Cmp_localize *cl = b->cmp_localize;
    Cmp_localize_group_info *g;
    int i;
    IntSet funcset, subrset;

    if (cmp_static_global_assign_array) {
        construct_sb_set_in_lm_assigned(b, &funcset, &subrset, level);
    }

    if (cl == NULL || cl->memory_level != level) {
        return;
    }

    if (cmp_array) {
        for (i = 1; i <= cl->amax; i++) {
            g = get_group_info_entry(cl, i);
            if (in_IntSet(cl->local_array, i) && g != NULL) {
                Array_table *ltbl;
                int oentry;

                if (cmp_ya_templ) {
                    ltbl = search_array_table(b->module->array_head,
                                              g->cl_tbl[i]);
                } else {
                    ltbl = search_array_table(g->lhead, g->cl_tbl[i]);
                }

                oentry = get_outer_block_array_entry(b, i);

                change_array_entry(b, oentry, ltbl);
                change_dtu_trans_group_entry_block(b, oentry, ltbl,
                                                   KIND_ARRAY);
                change_array_entry_module(b, oentry, funcset, subrset, g,
                                          level);
            }
        }
    }

    if (cmp_scalar) {
        for (i = 1; i < cl->vnum; i++) {
            g = get_var_group_info_entry(cl, i);
            if (in_IntSet(cl->local_var, i) && g != NULL) {
                Var_table *ltbl = search_var_table(g->vlhead, g->vcl_tbl[i]);
                int oentry;

                oentry = get_outer_block_scalar_entry(b, i);

                change_var_entry(b, oentry, ltbl);
                change_dtu_trans_group_entry_block(b, oentry, ltbl,
                                                   KIND_VAR);
            }
        }
    }
}
