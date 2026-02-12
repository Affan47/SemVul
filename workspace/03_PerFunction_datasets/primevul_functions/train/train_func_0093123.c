PointToCELL(TScreen *screen,
	    int y,
	    int x,
	    CELL *cell)


{
    cell->row = (y - screen->border) / FontHeight(screen);
    if (cell->row < screen->firstValidRow)
	cell->row = screen->firstValidRow;
    else if (cell->row > screen->lastValidRow)
	cell->row = screen->lastValidRow;
    cell->col = (x - OriginX(screen)) / FontWidth(screen);
    if (cell->col < 0)
	cell->col = 0;
    else if (cell->col > MaxCols(screen)) {
	cell->col = MaxCols(screen);
    }
#if OPT_WIDE_CHARS


    if (cell->col > 0
	&& isWideCell(cell->row, cell->col - 1)
	&& (XTERM_CELL(cell->row, cell->col) == HIDDEN_CHAR)) {
	cell->col -= 1;
    }
#endif
}
