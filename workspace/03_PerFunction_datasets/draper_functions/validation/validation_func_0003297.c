matrix_XTX_in_place (gretl_matrix *m)
{
    gretl_matrix *R = gretl_matrix_alloc(m->cols, m->cols);
    int err;

    if (R == NULL) {
	err = E_ALLOC;
    } else {
	err = gretl_matrix_multiply_mod(m, GRETL_MOD_TRANSPOSE,
					m, GRETL_MOD_NONE,
					R, GRETL_MOD_NONE);
    }

    if (!err) {
	matrix_cannibalize(m, R);
    }

    gretl_matrix_free(R);

    return err;
}
