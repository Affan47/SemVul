gnm_expr_entry_global_range_name (GnmExprEntry *gee, Sheet *sheet)
{
	GnmValue *val;
	char *text = NULL;

	g_return_val_if_fail (IS_GNM_EXPR_ENTRY (gee), NULL);

	val = gnm_expr_entry_parse_as_value (gee, sheet);
	if (val != NULL) {
		if (val->type == VALUE_CELLRANGE)
			text = value_get_as_string (val);
		value_release (val);
	}

	return text;
}
