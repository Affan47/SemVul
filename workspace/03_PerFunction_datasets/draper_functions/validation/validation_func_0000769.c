DisplayTiles(void)
{
    int Line, peg, SlotNo;
    char TileBuf[BUFSIZ];

    erase();
    mvaddstr(1, 24, "T O W E R S   O F   H A N O I");
    mvaddstr(3, 34, "SJR 1990");
    mvprintw(19, 5, "Moves : %d", NMoves);
    attrset(A_REVERSE);
    mvaddstr(BASELINE, 8,
	     "                                                               ");

    for (Line = TOPLINE; Line < BASELINE; Line++) {
	mvaddch(Line, LEFTPEG, ' ');
	mvaddch(Line, MIDPEG, ' ');
	mvaddch(Line, RIGHTPEG, ' ');
    }
    mvaddch(BASELINE, LEFTPEG, '1');
    mvaddch(BASELINE, MIDPEG, '2');
    mvaddch(BASELINE, RIGHTPEG, '3');
    attrset(A_NORMAL);


    for (peg = 0; peg < NPEGS; peg++) {
	for (SlotNo = 0; SlotNo < Pegs[peg].Count; SlotNo++) {
	    unsigned len = Pegs[peg].Length[SlotNo];
	    if (len < sizeof(TileBuf) - 1 && len < (unsigned) PegPos[peg]) {
		memset(TileBuf, ' ', len);
		TileBuf[len] = '\0';
		if (has_colors())
		    attrset(COLOR_PAIR(LENTOIND(len)));
		else
		    attrset(A_REVERSE);
		mvaddstr(BASELINE - (SlotNo + 1),
			 (int) (PegPos[peg] - len / 2),
			 TileBuf);
	    }
	}
    }
    attrset(A_NORMAL);
    refresh();
}
