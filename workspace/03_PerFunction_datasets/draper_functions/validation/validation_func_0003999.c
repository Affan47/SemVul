cpl_matrix_transpose_create(const cpl_matrix *matrix)
{


    cpl_matrix  *transposed = NULL;
    cpl_size     i, j;
    double      *m;
    double      *tm;


    if (matrix == NULL) {
        cpl_error_set_(CPL_ERROR_NULL_INPUT);
        return NULL;
    }


    tm = (double *)cpl_malloc((size_t)matrix->nc * (size_t)matrix->nr
                              * sizeof(*tm));
    transposed = cpl_matrix_wrap(matrix->nc, matrix->nr, tm);
    m = matrix->m;

    for (i = 0; i < matrix->nr; i++)
        for (j = 0, tm = transposed->m + i;
             j < matrix->nc; j++, tm += matrix->nr)
            *tm = *m++;

    return transposed;

}
