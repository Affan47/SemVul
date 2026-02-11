bond_opt_get_val(unsigned int option, u64 val)
{
	const struct bond_option *opt;
	int i;

	opt = bond_opt_get(option);
	if (WARN_ON(!opt))
		return NULL;
	for (i = 0; opt->values && opt->values[i].string; i++)
		if (opt->values[i].value == val)
			return &opt->values[i];

	return NULL;
}
