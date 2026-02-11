gnumeric_accrintm (GnmFuncEvalInfo *ei, GnmValue const * const *argv)
{
	gnm_float rate, a, d, par;
	int basis;
	GODateConventions const *date_conv =
		workbook_date_conv (ei->pos->sheet->workbook);

	rate  = value_get_as_float (argv[2]);
	par   = argv[3] ? value_get_as_float (argv[3]) : 1000;
	basis = value_get_basis (argv[4], GO_BASIS_MSRB_30_360);

	a = days_monthly_basis (argv[0], argv[1], basis, date_conv);
	d = annual_year_basis (argv[0], basis, date_conv);

	if (a < 0 || d <= 0 || par <= 0 || rate <= 0
	    || !is_valid_basis (basis))
                return value_new_error_NUM (ei->pos);

	return value_new_float (par * rate * a/d);
}
