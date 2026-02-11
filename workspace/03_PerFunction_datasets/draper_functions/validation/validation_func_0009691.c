ponnuki_connect(int *moves, int str1, int str2, zone *zn)
{
  int r, s, k, res = 0;
  int liberties, libs[MAXLIBS];
  int adj, adjs[MAXCHAIN];
  int neighb, neighbs[MAXCHAIN];


  liberties = findlib(str1, MAXLIBS, libs);
  for (r = 0; r < liberties; r++)
    if (is_self_atari(libs[r], OTHER_COLOR(board[str1])))
      for (k = 0; k < 4; k++) {
	int pos = libs[r] + delta[k];
	if (board[pos] == board[str1]
	    && !same_string(pos, str1)
	    && !same_string(pos, str2)) {


	  neighb = findlib(pos, MAXLIBS, neighbs);
	  for (s = 0; s < neighb; s++)
	    if (liberty_of_string(neighbs[s], str2)) {
	      res = 1;
	      add_zone(zn, libs[r]);
	      add_zone(zn, neighbs[s]);
	      add_array(moves, neighbs[s]);
	    }

	  adj = chainlinks2(pos, adjs, 1);
	  for (s = 0; s < adj; s++)
	    if (adjacent_strings(adjs[s], str2)
		&& !snapback(adjs[s])) {
	      res = 1;
	      neighb = findlib(adjs[s], 1, neighbs);
	      add_zone(zn, libs[r]);
	      add_zone(zn, neighbs[0]);
	      add_array(moves, neighbs[0]);
	    }
	}
      }

  return res;
}
