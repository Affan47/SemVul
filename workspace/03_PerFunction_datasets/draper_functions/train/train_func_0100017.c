destroy_board_list()
{
  Board *board;

  while(g_list_length(board_list)>0)
    {
      board = g_list_nth_data(board_list, 0);
      board_list = g_list_remove (board_list, board);
      destroy_board(board);
    }
}
