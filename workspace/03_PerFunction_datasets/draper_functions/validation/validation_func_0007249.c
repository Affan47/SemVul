board_diff_score() const
{
	int	score = 0;
	board_iterator	iter;
	iter.init_pos();
	do {
		score += board[iter.pos];
	} while (iter.next());
	return score;
}
