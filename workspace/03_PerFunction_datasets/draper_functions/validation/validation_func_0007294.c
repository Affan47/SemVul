cmd_pgnreplay(void)
{
  char tmp_epd[]=".tmp.epd";
  char data[MAXSTR]="";
  FILE *epdfile=NULL;
  char epdline[MAXSTR]="";

  PGNReadFromFile (token[1],1);

  SaveEPD( tmp_epd );
  epdfile = fopen( tmp_epd, "r" );
  if ( fgets( epdline, MAXSTR, epdfile ) == NULL ) {
    printf( _("Incorrect epd file\n") );
    return;
  }

  strcpy( data, "setboard " );
  int i=0;
  while ( epdline[i] != '\n' ) {
    data[i+9] = epdline[i];
    ++i;
  }
  data[i+9] = '\0';

  SetDataToEngine( data );
  SetAutoGo( true );

  pgnloaded = 1;
  pgncnt = GameCnt;

  while (GameCnt >= 0) {
    if (GameCnt >= 0) {
      CLEAR (flags, ENDED);
      CLEAR (flags, TIMEOUT);
      ChangeColor( true );
      SetAutoGo( true );
      UnmakeMove (board.side, &Game[GameCnt].move);
      if (GameCnt >= 0) {
        UnmakeMove (board.side, &Game[GameCnt].move);
      }
    }
  }

  cmd_first();
}
