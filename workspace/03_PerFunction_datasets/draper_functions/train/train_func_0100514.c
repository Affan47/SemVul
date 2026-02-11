towers_get_render (Pos *pos, byte *move, int **rmovp)
{
	static int rmove[512];
	int *rp = rmove;
	int i, j;
	for (i=0; i<board_wid; i++)
	for (j=0; j<board_heit; j++)
		if (pos->render[j * board_wid + i] != RENDER_NONE)
		{
			*rp++ = i;
			*rp++ = j;
			*rp++ = RENDER_NONE;
		}
	*rp++ = -1;
	*rmovp = rmove;
}
