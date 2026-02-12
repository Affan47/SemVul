R_API int r_anal_var_count_locals(RAnalFunction *fcn) {

	int args = r_anal_var_count_args (fcn);
	return r_anal_var_count_all (fcn) - args;
}
