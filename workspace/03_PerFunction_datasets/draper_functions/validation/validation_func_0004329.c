do_trymove(int pos, int color, int ignore_ko)
{

  gg_assert(color == BLACK || color == WHITE);

  if (pos != PASS_MOVE) {

    ASSERT_ON_BOARD1(pos);


    shadow[pos] = 1;


    if (board[pos] != EMPTY)
      return 0;


    if (!ignore_ko && pos == board_ko_pos) {
      if (board[WEST(pos)] == OTHER_COLOR(color)
	  || board[EAST(pos)] == OTHER_COLOR(color)) {
	return 0;
      }
    }


    if (is_suicide(pos, color))
      return 0;
  }


  if (stackp >= MAXSTACK-2) {
    fprintf(stderr,
	    "gnugo: Truncating search. This is beyond my reading ability!\n");

    if (0) {
      ASSERT1(0 && "trymove stack overflow", pos);
    }
#if 0
    if (verbose > 0) {
      showboard(0);
      dump_stack();
    }
#endif
    fflush(stderr);
    return 0;
  }


  trymove_counter++;


  stack[stackp] = pos;
  move_color[stackp] = color;

  really_do_trymove(pos, color);

  return 1;
}
