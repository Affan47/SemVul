openGeometry()
{
  int i;
  char filename[PATH_MAX];

  for(i = 0; i < geometryFiles; ++i)
    {

      manager->openStream(geometryFileStream[i], extension[i], std::ios::in);
    }


  int ftypes;
  fstream& str = geometryFileStream[HEADER];
  str >> bodies;
  str >> boundaries;
  str >> outer;
  str >> inner;
  str >> vertices;
  str >> loops;
  str >> maxloop;
  return 0;
}
