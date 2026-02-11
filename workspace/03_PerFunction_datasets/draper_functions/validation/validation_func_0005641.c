decide_connection(int apos, int bpos)
{
  int move;
  int result;
  SGFTree tree;

  ASSERT_ON_BOARD1(apos);
  ASSERT_ON_BOARD1(bpos);

  if (board[apos] == EMPTY || board[bpos] == EMPTY) {
    fprintf(stderr, "gnugo: --decide-connection called on an empty vertex\n");
    return;
  }

  if (board[apos] != board[bpos]) {
    fprintf(stderr, "gnugo: --decide-connection called for strings of different colors\n");
    return;
  }

  if (*outfilename)
    sgffile_begindump(&tree);


  reset_engine();

  count_variations = 1;
  result = string_connect(apos, bpos, &move);
  if (result == WIN) {
    if (move == NO_MOVE)
      gprintf("%1m and %1m are connected as it stands (%d variations)\n",
	      apos, bpos, count_variations);
    else
	gprintf("%1m and %1m can be connected at %1m (%d variations)\n",
		apos, bpos, move, count_variations);
  }
  else if (result == KO_A)
    gprintf("%1m and %1m can be connected with ko (good) at %1m (%d variations)\n",
	    apos, bpos, move, count_variations);
  else if (result == KO_B)
    gprintf("%1m and %1m can be connected with ko (bad) at %1m (%d variations)\n",
	    apos, bpos, move, count_variations);
  else
    gprintf("%1m and %1m cannot be connected (%d variations)\n",
	    apos, bpos, count_variations);

  count_variations = 1;
  result = disconnect(apos, bpos, &move);
  if (result == WIN) {
    if (move == NO_MOVE)
      gprintf("%1m and %1m are disconnected as it stands (%d variations)\n",
	      apos, bpos, count_variations);
    else
	gprintf("%1m and %1m can be disconnected at %1m (%d variations)\n",
		apos, bpos, move, count_variations);
  }
  else if (result == KO_A)
    gprintf("%1m and %1m can be disconnected with ko (good) at %1m (%d variations)\n",
	    apos, bpos, move, count_variations);
  else if (result == KO_B)
    gprintf("%1m and %1m can be disconnected with ko (bad) at %1m (%d variations)\n",
	    apos, bpos, move, count_variations);
  else
    gprintf("%1m and %1m cannot be disconnected (%d variations)\n",
	    apos, bpos, count_variations);

  sgffile_enddump(outfilename);
  count_variations = 0;
}
