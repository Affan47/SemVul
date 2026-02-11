set_time_double_value (biff_workbook * workbook, unsigned int row,
		       unsigned short col, double num)
{

    biff_cell_value *p_cell;
    char *string;
    char buf[64];
    unsigned int len;
    int h;
    int m;
    int s;
    int count = (int) floor (num);
    double percent = num - (double) count;

    if (workbook->active_sheet == NULL)
	return FREEXL_ILLEGAL_CELL_ROW_COL;
    if (workbook->active_sheet->cell_values == NULL)
	return FREEXL_ILLEGAL_CELL_ROW_COL;
    if (row >= workbook->active_sheet->rows
	|| col >= workbook->active_sheet->columns)
	return FREEXL_ILLEGAL_CELL_ROW_COL;

    compute_time (&h, &m, &s, percent);
    sprintf (buf, "%02d:%02d:%02d", h, m, s);
    len = strlen (buf);
    string = malloc (len + 1);
    if (!string)
	return FREEXL_INSUFFICIENT_MEMORY;
    strcpy (string, buf);

    p_cell =
	workbook->active_sheet->cell_values +
	(row * workbook->active_sheet->columns) + col;
    p_cell->type = FREEXL_CELL_TIME;
    p_cell->value.text_value = string;
    return FREEXL_OK;
}
