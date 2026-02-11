goBoard_rmGroup(GoBoard *board, int loc)  {
  GoBoardPiece  *oppList[4];
  GoBoardPiece  *dead, *neighbor;
  GoStone  s, o;
  int  i, j, oppListLen;

  assert(goStone_isStone(board->pieces[loc].type));
  dead = board->pieces[loc].head;
  s = dead->type;
  assert(goStone_isStone(s));
  o = goStone_opponent(s);
  board->caps[o] += dead->size;
  do  {
    board->hashVal = goHash_xor(board->hashVal,
				dead->hashStone[s]);
    dead->type = goStone_empty;
    dead->head = NULL;
    oppListLen = 0;
    for (i = 0;  i < 4;  ++i)  {
      neighbor = dead + board->dirs[i];
      if (neighbor->type == o)  {
	neighbor = neighbor->head;
	++neighbor->libs;
	for (j = 0;  j < oppListLen;  ++j)  {
	  if (oppList[j] == neighbor)  {
	    --neighbor->libs;
	    break;
	  }
	}
	oppList[oppListLen++] = neighbor;
      }
    }
    dead = dead->next;
  } while (dead);
}
