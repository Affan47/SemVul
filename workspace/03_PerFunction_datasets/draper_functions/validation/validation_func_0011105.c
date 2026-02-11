go_continued_fraction (double val, int max_denom, int *res_num, int *res_denom)
{
	int n1, n2, d1, d2;
	double x, y;

	if (val < 0) {
		go_continued_fraction (-val, max_denom, res_num, res_denom);
		*res_num = -*res_num;
		return;
	}

	n1 = 0; d1 = 1;
	n2 = 1; d2 = 0;

	x = val;
	y = 1;

	do {
		double a = floor (x / y);
		double newy = x - a * y;
		int ia, n3, d3;

		if ((n2 && a > (INT_MAX - n1) / n2) ||
		    (d2 && a > (INT_MAX - d1) / d2) ||
		    a * d2 + d1 > max_denom) {
			*res_num = n2;
			*res_denom = d2;
			return;
		}

		ia = (int)a;
		n3 = ia * n2 + n1;
		d3 = ia * d2 + d1;

		x = y;
		y = newy;

		n1 = n2; n2 = n3;
		d1 = d2; d2 = d3;
	} while (y > 1e-10);

	*res_num = n2;
	*res_denom = d2;
}
