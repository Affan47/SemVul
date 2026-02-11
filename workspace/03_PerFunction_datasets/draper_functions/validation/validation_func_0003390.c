filter_matrix (gretl_matrix *X, gretl_vector *A, gretl_vector *C,
			     double y0, int *err)
{
    int r = X->rows;
    int c = X->cols;
    gretl_matrix *Y = NULL;
    double *a = NULL, *b = NULL;
    int i, j;

    Y = gretl_matrix_alloc(r, c);
    a = malloc(r * sizeof *a);
    b = malloc(r * sizeof *b);

    if (Y == NULL || a == NULL || b == NULL) {
	*err = E_ALLOC;
	return NULL;
    }

    for (j=0; j<c; j++) {
	for (i=0; i<r; i++) {
	    a[i] = gretl_matrix_get(X, i, j);
	}
	*err = filter_vector(a, b, 0, r-1, A, C, y0);
	if (*err) {
	    break;
	} else {
	    for (i=0; i<r; i++) {
		gretl_matrix_set(Y, i, j, b[i]);
	    }
	}
    }

    free(a);
    free(b);

    return Y;
}
