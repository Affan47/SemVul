columnToCell(TScreen *screen, int row, int col, CELL *cell)
{
    while (row < screen->max_row) {
	CLineData *ld = GET_LINEDATA(screen, row);
	int last = LastTextCol(screen, ld, row);


	if (col <= last) {
	    break;
	}


	if (!LineTstWrapped(ld)) {
	    col = last + 1;
	    break;
	}
	col -= (last + 1);
	++row;
    }
    if (col < 0)
	col = 0;
    cell->row = row;
    cell->col = col;
}
