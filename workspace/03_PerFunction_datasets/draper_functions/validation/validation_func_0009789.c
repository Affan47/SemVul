have_declared_size_and_comparable(const Array_region_list_semnode *src1,
                                  const Array_region_list_semnode *src2,
                                  const int diff_dim,
                                  const Array_table *atbl)
{
    const Array_range_semnode *r1, *r2;
    int dim;
    int bas, lim;
    SemTree *t, *u, *l;
    SemTree *ct1;
    int c;

    if (atbl == NULL
	|| is_assumed_size_dummy_array(atbl)
	|| is_adjustable_array(atbl)) {
        return FALSE;
    }

    bas = atbl->bas.ct[diff_dim];
    lim = atbl->lim.ct[diff_dim];

    for (r1 = src1->dim_head, r2 = src2->dim_head, dim = 0;
         r1 != NULL && r2 != NULL && dim < diff_dim;
         r1 = r1->next_dim, r2 = r2->next_dim, dim++);

    if (r1->lower_tree == NULL
        || r1->upper_tree == NULL
        || r2->lower_tree == NULL
        || r2->upper_tree == NULL) {
        return FALSE;
    }

    if (semtree_is_const(r1->lower_tree)
        && (int)semtree_to_double(r1->lower_tree) == bas
        && semtree_is_const(r2->upper_tree)
        && (int)semtree_to_double(r2->upper_tree) == lim) {
        u = r1->upper_tree;
        l = r2->lower_tree;
    } else if (semtree_is_const(r1->upper_tree)
        && (int)semtree_to_double(r1->upper_tree) == lim
        && semtree_is_const(r2->lower_tree)
        && (int)semtree_to_double(r2->lower_tree) == bas) {
        u = r2->upper_tree;
        l = r1->lower_tree;
    } else {
        return FALSE;
    }

    ct1 = make_semtree_const_int(1);
    t = make_semtree(OPE_ADD, u, ct1);
    semtree_process(t);
    c = compare_semtree(t, l);

    semtree_destruct(t);
    semtree_destruct(ct1);

    return (c == 0 || c == 1);
}
