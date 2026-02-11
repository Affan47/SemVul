print_pw_qpolynomial_fold_isl(
	__isl_take isl_printer *p, __isl_keep isl_pw_qpolynomial_fold *pwf)
{
	if (isl_space_dim(pwf->dim, isl_dim_param) > 0) {
		p = print_tuple(pwf->dim, p, isl_dim_param, 0, NULL, NULL);
		p = isl_printer_print_str(p, " -> ");
	}
	p = isl_printer_print_str(p, "{ ");
	if (pwf->n == 0) {
		if (!isl_space_is_set(pwf->dim)) {
			p = print_tuple(pwf->dim, p, isl_dim_in, 0, NULL, NULL);
			p = isl_printer_print_str(p, " -> ");
		}
		p = isl_printer_print_str(p, "0");
	}
	p = isl_pwf_print_isl_body(p, pwf);
	p = isl_printer_print_str(p, " }");
	return p;
}
