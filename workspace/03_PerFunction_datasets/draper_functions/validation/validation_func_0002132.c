readMatchState( const char *string, const Game *game,
		    MatchState *state )
{
  int c, r;


  if( sscanf( string, "MATCHSTATE:%"SCNu8"%n",
	      &state->viewingPlayer, &c ) < 1
      || state->viewingPlayer >= game->numPlayers )  {
    return -1;
  }


  r = readStateCommon( &string[ c ], game, &state->state );
  if( r < 0 ) {
    return -1;
  }
  c += r;

  return c;
}
