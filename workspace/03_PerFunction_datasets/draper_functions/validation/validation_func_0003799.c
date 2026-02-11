cmd_level(void)
{
  SetDataToEngine( token[0] );
  sscanf (token[1], "%d %f %d", &TCMove, &TCTime, &TCinc);
  if (TCMove == 0) {
    TCMove =  35 ;
    printf("TCMove = %d\n",TCMove);
  }
  if (TCTime == 0) {
    SearchTime = TCinc / 2.0f ;
    printf(_("Fischer increment of %d seconds\n"),TCinc);
  } else {
    MoveLimit[white] = MoveLimit[black] = TCMove - (GameCnt+1)/2;
    TimeLimit[white] = TimeLimit[black] = TCTime * 60;
    if (!(flags & XBOARD)) {


      printf (_("Time Control: %d moves in %.2f secs\n"),
      MoveLimit[white], TimeLimit[white]);
      printf(_("Fischer increment of %d seconds\n"),TCinc);
    }
  }
}
