getMission ()
{
  Mission *m = new MissionCustom ();
  m->id = mapptr;
  m->init ();
  return m;
}
