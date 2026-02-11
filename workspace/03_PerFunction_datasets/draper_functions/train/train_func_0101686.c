gnm_style_conditions_new (Sheet *sheet)
{
	GnmStyleConditions *res;
	g_return_val_if_fail (IS_SHEET (sheet), NULL);

	res = g_object_new (gnm_style_conditions_get_type (), NULL);
	res->sheet = sheet;
	return res;
}
