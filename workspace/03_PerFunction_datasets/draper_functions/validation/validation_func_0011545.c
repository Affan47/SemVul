hash_pawn_key(const board_t * board) {

   uint64 key;
   int colour;
   const sq_t * ptr;
   int sq, piece;

   ASSERT(board!=NULL);


   key = 0;


   for (colour = 0; colour < ColourNb; colour++) {
      for (ptr = &board->pawn[colour][0]; (sq=*ptr) != SquareNone; ptr++) {
         piece = board->square[sq];
         key ^= hash_piece_key(piece,sq);
      }
   }

   return key;
}
