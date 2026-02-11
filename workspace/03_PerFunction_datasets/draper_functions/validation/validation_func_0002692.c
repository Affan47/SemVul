matrix_and_or (NODE *l, NODE *r, int op, parser *p)
{
    NODE *ret = aux_matrix_node(p);

    if (ret != NULL && starting(p)) {
	const gretl_matrix *a = l->v.m;
	const gretl_matrix *b = r->v.m;
	int i, n = a->rows * a->cols;

	if (gretl_is_null_matrix(a) || gretl_is_null_matrix(b)) {
	    p->err = E_NONCONF;
	} else if (a->rows != b->rows || a->cols != b->cols) {
	    p->err = E_NONCONF;
	} else {
	    ret->v.m = gretl_unit_matrix_new(a->rows, a->cols);
	    if (ret->v.m == NULL) {
		p->err = E_ALLOC;
		return NULL;
	    }
	    for (i=0; i<n; i++) {
		if (op == B_AND) {
		    if (a->val[i] == 0.0 || b->val[i] == 0.0) {
			ret->v.m->val[i] = 0.0;
		    }
		} else if (op == B_OR) {
		    if (a->val[i] == 0.0 && b->val[i] == 0.0) {
			ret->v.m->val[i] = 0.0;
		    }
		}
	    }
	}
    }

    return ret;
}
