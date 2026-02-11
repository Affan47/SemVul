connect_and_cut_helper2(int Apos, int bpos, int cpos, int color)
{
  int dpos;
  int epos = NO_MOVE;
  int other = OTHER_COLOR(color);
  int result = 0;
  int k;

  gg_assert(IS_STONE(color));


  if (TRYMOVE(Apos, color)) {
    for (k = 0; k < 4; k++)
      if (board[cpos + delta[k]] == other
	  && neighbor_of_string(cpos + delta[k], Apos)) {
	epos = cpos + delta[k];
	break;
      }

    gg_assert(epos != NO_MOVE);

    if (TRYMOVE(bpos, other)) {
      if (!find_defense(Apos, &dpos) || dpos == NO_MOVE) {
	popgo();
	popgo();
	return 0;
      }

      if (TRYMOVE(dpos, color)) {
	if (TRYMOVE(cpos, color)) {
	  if (board[bpos] == EMPTY
	      || board[epos] == EMPTY
	      || !defend_both(bpos, epos))
	    result = 1;
	  popgo();
	}
	popgo();
      }
      popgo();
    }
    popgo();
  }

  return result;
}
