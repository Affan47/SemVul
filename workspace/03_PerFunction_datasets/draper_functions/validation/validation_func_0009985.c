isl_mat_col_add(__isl_keep isl_mat *mat, int dst_col, int src_col)
{
	int i;

	if (!mat)
		return;

	for (i = 0; i < mat->n_row; ++i)
		isl_int_add(mat->row[i][dst_col],
			    mat->row[i][dst_col], mat->row[i][src_col]);
}
