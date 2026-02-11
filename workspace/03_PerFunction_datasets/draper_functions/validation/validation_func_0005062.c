backOk(void *packet)  {
  Local  *l = packet;
  GoGame  *game;

  assert(MAGIC(l));
  game = l->game;
  switch(game->state)  {
  case(goGameState_selectDead):
    return(TRUE);
    break;
  case(goGameState_selectDisputed):
    return(FALSE);
    break;
  case(goGameState_dispute):
    return(game->moveNum > game->setWhoseMoveNum);
    break;
  default:
    return(game->moveNum > 0);
    break;
  }
}
