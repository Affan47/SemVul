gnm_sheet_filter_at_pos (Sheet const *sheet, GnmCellPos const *pos)
{
	GSList *ptr;
	GnmRange r;

	g_return_val_if_fail (IS_SHEET (sheet), NULL);
	g_return_val_if_fail (NULL != pos, NULL);

	range_init_cellpos (&r, pos);
	for (ptr = sheet->filters; ptr != NULL ; ptr = ptr->next)
		if (gnm_filter_overlaps_range (ptr->data, &r))
			return ptr->data;

	return NULL;
}
