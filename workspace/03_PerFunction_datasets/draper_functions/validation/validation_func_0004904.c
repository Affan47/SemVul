stop (int sample)
{
  if (!audio) return;
  switch (sample)
  {
    case SOUND_CLICK1:
      waveclick1->stop ();
      break;
    case SOUND_CANNON1:
      wavecannon1->stop ();
      break;
    case SOUND_MISSILE1:
      wavemissile1->stop ();
      break;
    case SOUND_EXPLOSION1:
      waveexplosion1->stop ();
      break;
    case SOUND_THUNDER1:
      wavethunder1->stop ();
      break;
    case SOUND_PLANE1:
      waveplane [0]->stop ();
      break;
    case SOUND_HIT1:
      wavehit1->stop ();
      break;
    case SOUND_BEEP1:
      wavebeep1->stop ();
      break;
    case SOUND_CHAFF1:
      wavechaff1->stop ();
      break;
    case SOUND_BEEP2:
      wavebeep2->stop ();
      break;
  }
}
