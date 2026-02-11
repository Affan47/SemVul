mpw_invert (mpw_ptr rop, mpw_ptr op1, mpw_ptr mod)
{
	if G_LIKELY (MPW_IS_REAL (op1) && MPW_IS_REAL (mod)) {
		MAKE_REAL (rop);
		if (rop != op1 && rop != mod) {
			MAKE_EMPTY (rop->r, MPW_INTEGER);
		} else {
			MAKE_COPY (rop->r);
		}
		if G_UNLIKELY ( ! mpwl_invert (rop->r, op1->r, mod->r)) {
			if (op1->r->type == MPW_INTEGER &&
			    mod->r->type == MPW_INTEGER) {
				char *n1, *n2;


				n1 = mpwl_getstring_for_error (op1->r);
				n2 = mpwl_getstring_for_error (mod->r);
				gel_error_num = GEL_NUMERICAL_MPW_ERROR;
				gel_errorout (_("Inverse of %s modulo "
						"%s not found!"),
					      n1, n2);
				g_free (n1);
				g_free (n2);
			}
		}
	} else {
		gel_error_num=GEL_NUMERICAL_MPW_ERROR;
		gel_errorout (_("Can't do modulo invert on complex numbers"));
	}
}
