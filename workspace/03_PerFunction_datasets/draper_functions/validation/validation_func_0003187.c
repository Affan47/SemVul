next_non_integer_var(struct isl_tab *tab, int var, int *f)
{
	var = var < 0 ? tab->n_param : var + 1;

	for (; var < tab->n_var - tab->n_div; ++var) {
		int flags = 0;
		int row;
		if (!tab->var[var].is_row)
			continue;
		row = tab->var[var].index;
		if (integer_constant(tab, row))
			ISL_FL_SET(flags, I_CST);
		if (integer_parameter(tab, row))
			ISL_FL_SET(flags, I_PAR);
		if (ISL_FL_ISSET(flags, I_CST) && ISL_FL_ISSET(flags, I_PAR))
			continue;
		if (integer_variable(tab, row))
			ISL_FL_SET(flags, I_VAR);
		*f = flags;
		return var;
	}
	return -1;
}
