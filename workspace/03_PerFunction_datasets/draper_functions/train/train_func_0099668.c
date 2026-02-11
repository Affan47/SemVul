print_aff_c(__isl_take isl_printer *p,
	__isl_keep isl_aff *aff)
{
	unsigned total;

	total = isl_local_space_dim(aff->ls, isl_dim_all);
	if (!isl_int_is_one(aff->v->el[0]))
		p = isl_printer_print_str(p, "(");
	p = print_ls_partial_affine_c(p, aff->ls, aff->v->el + 1, 1 + total);
	if (!isl_int_is_one(aff->v->el[0])) {
		p = isl_printer_print_str(p, ")/");
		p = isl_printer_print_isl_int(p, aff->v->el[0]);
	}
	return p;
}
