prop_get_double_or(const char *name, double default_value)
{
	const char *prop = prop_get(name);
	double val;

	return (prop && sscanf(prop, "%lg", &val)) ? val : default_value;
}
