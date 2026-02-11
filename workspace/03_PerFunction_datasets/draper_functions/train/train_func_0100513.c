free_html_tbl(htmltbl_t * tbl)
{
    htmlcell_t **cells;

    if (tbl->rc == -1) {
	dtclose(tbl->u.p.rows);
    } else {
	cells = tbl->u.n.cells;

	free(tbl->heights);
	free(tbl->widths);
	while (*cells) {
	    free_html_cell(*cells);
	    cells++;
	}
	free(tbl->u.n.cells);
    }
    free_html_data(&tbl->data);
    free(tbl);
}
