is_pinned(const board_t * board, int from, int to, int colour) {

   int king;
   int inc;
   int sq, piece;

   ASSERT(board!=NULL);
   ASSERT(square_is_ok(from));
   ASSERT(square_is_ok(to));
   ASSERT(colour_is_ok(colour));

   king = king_pos(board,colour);

   inc = DELTA_INC(king-from);
   if (inc == IncNone) return false;

   sq = from;
   do sq += inc; while (board->square[sq] == Empty);

   if (sq != king) return false;

   sq = from;
   do sq -= inc; while ((piece=board->square[sq]) == Empty);

   return square_is_ok(sq)
       && (piece & DELTA_MASK(king-sq)) != 0
       && piece_colour(piece) == colour_opp(colour)
       && DELTA_INC(king-to) != inc;
}

}
