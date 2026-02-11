eval_disconnected (byte *theboard)
{
	byte board[KNIGHTS_BOARD_WID * KNIGHTS_BOARD_HEIT];
	int stack[KNIGHTS_BOARD_WID * KNIGHTS_BOARD_HEIT];
	int stack_top = 0;
	int i, curx, cury, x, y;

	for (i=0; i<board_wid * board_heit; i++)
		board[i] = theboard[i];

	get_cur_pos (board, WHITE, &curx, &cury);

	stack[stack_top++] = cury * board_wid + curx;
	while (stack_top > 0)
	{
		stack_top--;
		curx = stack[stack_top] % board_wid;
		cury = stack[stack_top] / board_wid;
		for (i=0; i<8; i++)
		{
			x = curx + incx[i];
			y = cury + incy[i];
			if (!ISINBOARD (x, y)) continue;
			if (board[y * board_wid + x] == KNIGHTS_BN)
				return FALSE;
			if (board[y * board_wid + x] != KNIGHTS_EMPTY)
				continue;
			board[y * board_wid + x] = KNIGHTS_CLOSED;
			stack[stack_top++] = y * board_wid + x;
		}
	}
	return TRUE;
}
