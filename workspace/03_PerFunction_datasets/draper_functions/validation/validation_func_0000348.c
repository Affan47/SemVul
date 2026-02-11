matrix_fill_func (NODE *l, NODE *r, int f, parser *p)
{
    NODE *ret = aux_matrix_node(p);

    if (ret != NULL && starting(p)) {
	int cols = 0, rows = node_get_int(l, p);

	if (!p->err) {
	    if (f == F_IMAT) {
		cols = rows;
	    } else {
		cols = node_get_int(r, p);
	    }
	}

	if (!p->err && !ok_matrix_dim(rows, cols, f)) {
	    p->err = E_INVARG;
	    matrix_error(p);
	}

	if (p->err) {
	    return ret;
	}

	switch (f) {
	case F_IMAT:
	    ret->v.m = gretl_identity_matrix_new(rows);
	    break;
	case F_ZEROS:
	    ret->v.m = gretl_zero_matrix_new(rows, cols);
	    break;
	case F_ONES:
	    ret->v.m = gretl_unit_matrix_new(rows, cols);
	    break;
	case F_MUNIF:
	    ret->v.m = gretl_random_matrix_new(rows, cols,
					       D_UNIFORM);
	    break;
	case F_MNORM:
	    ret->v.m = gretl_random_matrix_new(rows, cols,
					       D_NORMAL);
	    break;
	default:
	    break;
	}
    }

    return ret;
}
