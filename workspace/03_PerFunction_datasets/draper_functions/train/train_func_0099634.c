h1(const state& st){
	int** board = st.getBoard();
	int nMismatchedTiles = 0;
	if(board[0][0] != 1 && board[0][0] != 0)nMismatchedTiles++;
	if(board[0][1] != 2 && board[0][1] != 0)nMismatchedTiles++;
	if(board[0][2] != 3 && board[0][2] != 0)nMismatchedTiles++;
	if(board[1][0] != 8 && board[1][0] != 0)nMismatchedTiles++;
	if(board[1][2] != 4 && board[1][2] != 0)nMismatchedTiles++;
	if(board[2][0] != 7 && board[2][0] != 0)nMismatchedTiles++;
	if(board[2][1] != 6 && board[2][1] != 0)nMismatchedTiles++;
	if(board[2][2] != 5 && board[2][2] != 0)nMismatchedTiles++;
	return nMismatchedTiles;
}
