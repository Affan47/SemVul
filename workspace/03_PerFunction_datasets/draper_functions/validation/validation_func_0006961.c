expand_sb_array_range_semnode(Array_range_semnode *dim_head,
                              Array_table *callee_table)
{
    Array_range_semnode *rpt;
    int callee_dim = callee_table->dim;
    int i;

    for (i = 0, rpt = dim_head; i < callee_dim; i++, rpt = rpt->next_dim) {
        if (rpt->lower_tree == NULL || !semtree_is_const(rpt->lower_tree)
            || semtree_to_double(rpt->lower_tree) != callee_table->bas.ct[i]) {
            if (rpt->lower_tree != NULL) {
                semtree_destruct(rpt->lower_tree);
            }
            rpt->lower_tree = make_semtree_const_int(callee_table->bas.ct[i]);
        }
        if (rpt->upper_tree == NULL || !semtree_is_const(rpt->upper_tree)
            || semtree_to_double(rpt->upper_tree) != callee_table->lim.ct[i]) {
            if (rpt->upper_tree != NULL) {
                semtree_destruct(rpt->upper_tree);
            }
            rpt->upper_tree = make_semtree_const_int(callee_table->lim.ct[i]);
        }
    }
}
