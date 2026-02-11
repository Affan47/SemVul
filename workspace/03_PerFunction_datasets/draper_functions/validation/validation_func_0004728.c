user_matrix_unvech (const gretl_matrix *m, int *err)
{
    gretl_matrix *R = NULL;

    if (gretl_is_null_matrix(m)) {
	R = gretl_null_matrix_new();
    } else if (m->cols != 1) {
	*err = E_NONCONF;
    } else {
	int n = (int) ((sqrt(1.0 + 8.0 * m->rows) - 1.0) / 2.0);

	R = gretl_matrix_alloc(n, n);
	if (R != NULL) {
	    *err = gretl_matrix_unvectorize_h(R, m);
	}
    }

    if (R == NULL && !*err) {
	*err = E_ALLOC;
    }

    return R;
}
