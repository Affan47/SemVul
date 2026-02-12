ExtendExtend(XtermWidget xw, const CELL *cell)
{
    TScreen *screen = TScreenOf(xw);
    int coord = Coordinate(screen, cell);

    TRACE(("ExtendExtend row=%d, col=%d\n", cell->row, cell->col));
    if (screen->eventMode == LEFTEXTENSION
	&& ((coord + (screen->selectUnit != Select_CHAR))
	    > Coordinate(screen, &(screen->endSel)))) {

	screen->eventMode = RIGHTEXTENSION;
	screen->startExt = screen->saveStartR;
    } else if (screen->eventMode == RIGHTEXTENSION
	       && coord < Coordinate(screen, &(screen->startSel))) {

	screen->eventMode = LEFTEXTENSION;
	screen->endExt = screen->saveEndR;
    }
    if (screen->eventMode == LEFTEXTENSION) {
	screen->startExt = *cell;
    } else {
	screen->endExt = *cell;
    }
    ComputeSelect(xw, &(screen->startExt), &(screen->endExt), False, True);

#if OPT_READLINE
    if (!isSameCELL(&(screen->startSel), &(screen->endSel)))
	ExtendingSelection = 1;
#endif
}
