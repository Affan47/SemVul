sheet_style_default (Sheet const *sheet)
{
	g_return_val_if_fail (IS_SHEET (sheet), NULL);
	g_return_val_if_fail (sheet->style_data != NULL, NULL);

	gnm_style_ref (sheet->style_data->default_style);
	return sheet->style_data->default_style;
}
