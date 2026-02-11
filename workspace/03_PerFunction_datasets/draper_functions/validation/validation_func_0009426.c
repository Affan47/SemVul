xlsx_lookup_external_wb (GnmConventions const *convs,
			 G_GNUC_UNUSED Workbook *ref_wb,
			 char const *name)
{
	XLSXExprConventions const *xconv = (XLSXExprConventions const *)convs;
	if (strcmp (name, "0") == 0)
		return ref_wb;
	if (0) g_printerr ("lookup '%s'\n", name);
	return g_hash_table_lookup (xconv->extern_wb_by_id, name);
}
