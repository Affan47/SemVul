board_print_row(struct board *board, int y, char *s, char *end, board_cprint cprint)
{
	s += snprintf(s, end - s, " %2d | ", y);
	for (int x = 1; x < board_size(board) - 1; x++) {
		if (coord_x(board->last_move.coord, board) == x && coord_y(board->last_move.coord, board) == y)
			s += snprintf(s, end - s, "%c)", stone2char(board_atxy(board, x, y)));
		else
			s += snprintf(s, end - s, "%c ", stone2char(board_atxy(board, x, y)));
	}
	s += snprintf(s, end - s, "|");
	if (cprint) {
		s += snprintf(s, end - s, " %2d | ", y);
		for (int x = 1; x < board_size(board) - 1; x++) {
			s = cprint(board, coord_xy(board, x, y), s, end);
		}
		s += snprintf(s, end - s, "|");
	}
	s += snprintf(s, end - s, "\n");
	return s;
}
