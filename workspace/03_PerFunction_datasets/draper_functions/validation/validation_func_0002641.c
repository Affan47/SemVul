removeOrientation(list<Cone> const &triangulation)
{
  vector<list<int> > ret(triangulation.size());

  int I=0;
  for(list<Cone>::const_iterator i=triangulation.begin();i!=triangulation.end();i++,I++)
    ret[I]=*i;

  return ret;
}
