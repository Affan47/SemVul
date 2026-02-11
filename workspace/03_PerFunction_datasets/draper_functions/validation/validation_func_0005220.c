style_dep_unrender (GnmDependent *dep, const char *what)
{
	GnmCellPos const *pos = dependent_pos (dep);
	GnmCell *cell;
	Sheet *sheet = dep->sheet;

	if (debug_style_deps ())
		g_printerr ("StyleDep %p at %s %s\n",
			    dep, cellpos_as_string (pos), what);


	cell = sheet_cell_get (sheet, pos->col, pos->row);
	if (cell)
		gnm_cell_unrender (cell);

	sheet_redraw_region (sheet,
			     pos->col, pos->row,
			     pos->col, pos->row);


}
