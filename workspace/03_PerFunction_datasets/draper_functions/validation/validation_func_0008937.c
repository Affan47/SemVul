lu_backsub(
double **a,
int      n,
int     *pivx,
double  *b
) {
	int i, j;
	int nvi;


	for (nvi = -1, i = 0; i < n; i++) {
		int px;
		double sum;

		px = pivx[i];
		sum = b[px];
		b[px] = b[i];
		if (nvi >= 0) {
			for (j = nvi; j < i; j++)
				sum -= a[i][j] * b[j];
		} else {
			if (sum != 0.0)
				nvi = i;
		}
		b[i] = sum;
	}


	for (i = (n-1); i >= 0; i--) {
		double sum;
		sum = b[i];
		for (j = i+1; j < n; j++)
			sum -= a[i][j] * b[j];
		b[i] = sum/a[i][i];
	}
}
