make_ai_move()

{
  struct coords move;

  sleep(1);

  get_best_ai_move(&move);
  pieces[move.x][move.y] = current_player;
  if(current_player == WHITE) {
    current_player = BLACK;
  }
  else {
    current_player = WHITE;
  }
  draw_piece(pieces[move.x][move.y], square_windows[move.x][move.y]);
  flip_pieces(move);
  update_score_window("White = %d Black = %d");
  show_player_id();
  mark_legal_squares(current_player);

  return;
}
