switch_finish ()
{
  lasttime = 0;
  game = GAME_FINISH;
  creditstimer = 50 * timestep;
  credits_reshape ();
  if (sound->musicplaying)
    sound->haltMusic ();
  sound->loadMusic (MUSIC_ELECTRO1);
  sound->playMusic ();
  sound->stop (SOUND_PLANE1);
  sound->stop (SOUND_CANNON1);
}
