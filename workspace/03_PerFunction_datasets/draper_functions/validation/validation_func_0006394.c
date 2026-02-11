xml_not_used_old_array_spec (XMLSaxParseState *state,
			     GnmCell *cell, GnmCellCopy *cc,
			     char const *content)
{
	long rows, cols, row, col;

#if 0

	g_string_append_printf (str, "{%s}(%d,%d)[%d][%d]", expr_text,
		array.rows, array.cols, array.y, array.x);
#endif
	char *end, *expr_end, *ptr;

	if (content[0] != '=' || content[1] != '{')
		return TRUE;

	expr_end = strrchr (content, '}');
	if (expr_end == NULL || expr_end[1] != '(')
		return TRUE;

	rows = strtol (ptr = expr_end + 2, &end, 10);
	if (end == ptr || *end != ',')
		return TRUE;
	cols = strtol (ptr = end + 1, &end, 10);
	if (end == ptr || end[0] != ')' || end[1] != '[')
		return TRUE;
	row = strtol (ptr = end + 2, &end, 10);
	if (end == ptr || end[0] != ']' || end[1] != '[')
		return TRUE;
	col = strtol (ptr = end + 2, &end, 10);
	if (end == ptr || end[0] != ']' || end[1] != '\0')
		return TRUE;

	if (row == 0 && col == 0) {
		*expr_end = '\0';
		xml_cell_set_array_expr (state, cell, cc,
					 content + 2, rows, cols);
	}

	return FALSE;
}
