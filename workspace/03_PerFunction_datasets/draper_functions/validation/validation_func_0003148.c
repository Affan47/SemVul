hold_monster(void)
{
    short i, j;
    short mcount = 0;
    object *monster;
    short row, col;

    for (i = -2; i <= 2; i++) {
	for (j = -2; j <= 2; j++) {
	    row = rogue.row + i;
	    col = rogue.col + j;
	    if ((row < MIN_ROW) || (row > (ROGUE_LINES - 2)) || (col < 0) ||
		(col > (ROGUE_COLUMNS - 1))) {
		continue;
	    }
	    if (dungeon[row][col] & MONSTER) {
		monster = object_at(&level_monsters, row, col);
		monster->m_flags |= ASLEEP;
		monster->m_flags &= (~WAKENS);
		mcount++;
	    }
	}
    }
    if (mcount == 0) {
	message(mesg[269], 0);
    } else if (mcount == 1) {
	message(mesg[270], 0);
    } else {
	message(mesg[271], 0);
    }
}
