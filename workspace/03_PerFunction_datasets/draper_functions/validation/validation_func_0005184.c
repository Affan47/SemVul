workbook_sheet_state_size (const WorkbookSheetState *wss)
{
	int size = 1 + g_slist_length (wss->properties);
	int i;
	for (i = 0; i < wss->n_sheets; i++) {
		WorkbookSheetStateSheet *wsss = wss->sheets + i;
		size += 5;
		size += g_slist_length (wsss->properties);
	}
	return size;
}
