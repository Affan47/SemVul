parse_values(const char *s, struct value **values)
{
	const struct value *value;
	int n;

	scan_values(s);
	if (yyparse())
		return -1;
	*values = var_value_list;
	n = 0;
	for (value = var_value_list; value; value = value->next)
		n++;
	return n;
}
