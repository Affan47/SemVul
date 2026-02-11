delete_column (StfDialogData *pagedata, int col, gboolean test_only)
{
	int colcount = stf_parse_options_fixed_splitpositions_count (pagedata->parseoptions);
	if (col < 0 || col >= colcount - 1)
		return FALSE;

	if (!test_only) {
		int nextstart = stf_parse_options_fixed_splitpositions_nth (pagedata->parseoptions, col);
		stf_parse_options_fixed_splitpositions_remove (pagedata->parseoptions, nextstart);
		fixed_page_update_preview (pagedata);
	}
	return TRUE;
}
