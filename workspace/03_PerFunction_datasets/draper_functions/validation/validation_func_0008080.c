GMT_x_is_outside (double *x, double left, double right)
{


	if (GMT_is_dnan (*x)) return (TRUE);
	if (GMT_io.in_col_type[0] == GMT_IS_LON) {
		while ((*x) > left) (*x) -= 360.0;
		while ((*x) < left) (*x) += 360.0;
		return (((*x) > right) ? TRUE : FALSE);
	}
	else
		return (((*x) < left || (*x) > right) ? TRUE : FALSE);
}
