move_from_string(const char string[], const board_t * board) {

   char tmp_string[3];
   int from, to;
   int move;
   int piece, delta;

   ASSERT(string!=NULL);
   ASSERT(board!=NULL);


   tmp_string[0] = string[0];
   tmp_string[1] = string[1];
   tmp_string[2] = '\0';

   from = square_from_string(tmp_string);
   if (from == SquareNone) return MoveNone;


   tmp_string[0] = string[2];
   tmp_string[1] = string[3];
   tmp_string[2] = '\0';

   to = square_from_string(tmp_string);
   if (to == SquareNone) return MoveNone;

   move = MOVE_MAKE(from,to);


   switch (string[4]) {
   case '\0':
      break;
   case 'n':
      move |= MovePromoteKnight;
      break;
   case 'b':
      move |= MovePromoteBishop;
      break;
   case 'r':
      move |= MovePromoteRook;
      break;
   case 'q':
      move |= MovePromoteQueen;
      break;
   default:
      return MoveNone;
   }


   piece = board->square[from];

   if (PIECE_IS_PAWN(piece)) {
      if (to == board->ep_square) move |= MoveEnPassant;
   } else if (PIECE_IS_KING(piece)) {
      delta = to - from;
      if (delta == +2 || delta == -2) move |= MoveCastle;
   }

   return move;
}

}
