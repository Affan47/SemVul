isl_mat_rank(__isl_keep isl_mat *mat)
{
	int row, col;
	isl_mat *H;

	H = isl_mat_left_hermite(isl_mat_copy(mat), 0, NULL, NULL);
	if (!H)
		return -1;

	for (col = 0; col < H->n_col; ++col) {
		for (row = 0; row < H->n_row; ++row)
			if (!isl_int_is_zero(H->row[row][col]))
				break;
		if (row == H->n_row)
			break;
	}

	isl_mat_free(H);

	return col;
}
