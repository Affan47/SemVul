event_selectMissile ()
{
  if (!fplayer->active) return;
  fplayer->missiletype = fplayer->nextMissile (fplayer->missiletype);
}
