gen_sylv_solve(int order, int n, int m, int zero_cols,
					const double* A, const double* B,
					const double* C, double* X)
{
		GeneralSylvester s(order, n, m, zero_cols, A, B, C, X, false);
		s.solve();
}
