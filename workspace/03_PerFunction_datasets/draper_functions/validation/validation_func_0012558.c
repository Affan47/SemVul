collideEnemyShot( Vector2D posOld ) {
  switch (shotType) {
  case ENEMY_SHOT_NORMAL:
    {
      for ( unsigned int i = 0; i < racers->getNrRacers(); i++ ) {
	if ( racers->getRacer(i)->collidesWith( posOld, pos ) ) {
	  racers->getRacer(i)->doDamage( shotType );
	  timeToLive = 0;
	  collidedWithGround = false;
	  return true;
	}
      }
      break;
    }
  case ENEMY_SHOT_TANK_ROCKET:
    {
      for ( unsigned int i = 0; i < racers->getNrRacers(); i++ ) {
	if ( racers->getRacer(i)->collidesWith( Circle(pos, 5) ) ) {
	  racers->getRacer(i)->doDamage( shotType );
	  timeToLive = 0;
	  collidedWithGround = false;
	  return true;
	}
      }
      break;
    }
  default:
    {
      cout << "collideEnemyShot: unexpected shotType: " << shotType << endl;
      return false;
    }
  }
  return false;
}
