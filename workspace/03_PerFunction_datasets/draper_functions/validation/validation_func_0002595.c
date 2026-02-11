get_moments (const gretl_matrix *M, int row, double *skew, double *kurt)
{
    int j, n = gretl_matrix_cols(M);
    double dev, s[4] = {0.0};
    int err = 0;

    for (j=0; j<n; j++) {
	s[0] += gretl_matrix_get(M, row, j);
    }

    s[0] /= n;

    for (j=0; j<n; j++) {
	dev = gretl_matrix_get(M, row, j) - s[0];
	s[1] += dev * dev;
	s[2] += pow(dev, 3);
	s[3] += pow(dev, 4);
    }

    s[1] /= n;

    if (s[1] > 0.0) {
	*skew = (s[2] / n) / pow(s[1], 1.5);
	*kurt = ((s[3] / n) / pow(s[1], 2));
    } else {

	*skew = *kurt = NADBL;
	err = 1;
    }

    return err;
}
