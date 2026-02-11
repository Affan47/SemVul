handleSpontaneousFormationChange( int dT ) {
  nextFormationChange -= dT;
  if ( changeSpontaneous && nextFormationChange < 0 ) {

    chooseNewFormationType();
    moveEnemyInFormation();

    if ( changeOften ) {
      nextFormationChange =
	FORMATION_CHANGE_OFTEN_DELAY +
	rand() % (FORMATION_CHANGE_OFTEN_RAND_DELAY+1);
    } else if ( changeSeldom ) {
      nextFormationChange =
	FORMATION_CHANGE_SELDOM_DELAY +
	rand() % (FORMATION_CHANGE_SELDOM_RAND_DELAY+1);
    }
  }
}
