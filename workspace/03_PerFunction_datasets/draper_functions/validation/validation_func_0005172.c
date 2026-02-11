generate_sgc(int k)
{
    prec = 3;
    matrix_t **game = malloc(2*sizeof(matrix_t*));
    int i, j, jp, jn, m, n;
    m = n = (4 * k) - 1;
    game[0] = matrix_alloc(m, n);
    game[1] = matrix_alloc(m, n);
    matrix_t *A = game[0];
    matrix_t *B = game[1];
    for (i = 1; i < 2*k; i++)
    {
        if (i == 1)
            jn = 2 * k - 1;
        else
            jn = i - 1;

        if (i == 2 * k - 1)
            jp = 1;
        else
            jp = i + 1;

        A->data[a(i)][c(jp)] = 0.5;
        B->data[a(i)][c(jp)] = 1.;

        A->data[a(i)][c(jn)] = 1.;
        B->data[a(i)][c(jn)] = 0.5;

        for (j = 1; j <= 2*k; j++)
        {
            if (j != jp && j != jn && j != 2*k)
            {
                A->data[a(i)][c(j)] = 0.75;
                B->data[a(i)][c(j)] = 0.75;
            }

            A->data[a(i)][d(j)] = 0.5;

            if (j != 2*k)
                B->data[b(i)][c(j)] = 0.5;

            if (i % 2 == 1)
                B->data[b(i)][d(i + 1)] = 0.75;
            else
                B->data[b(i)][d(i - 1)] = 0.75;
        }
        A->data[b(i)][d(i)] = 0.75;
    }

    for (j = 1; j < 2*k; j++)
        B->data[b(i)][c(j)] = 0.5;

    B->data[b(i)][d(i - 1)] = 0.75;
    A->data[b(i)][d(i)] = 0.75;
    return game;
}
