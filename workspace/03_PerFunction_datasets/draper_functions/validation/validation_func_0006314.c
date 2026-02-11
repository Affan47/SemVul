gwy_delaunay_remove_point(GwyDelaunayMesh *m)
{
  gint i;
  simplex  *s;

  for (i=0; i< arrayListSize(m->conflicts); i++)
  {
    s = getFromArrayList(m->conflicts,i);
    addSimplexToMesh(m,s);
  }

  undoNeighbourUpdates(m->neighbourUpdates);

  for (i=0; i<arrayListSize(m->updates); i++)
  {
    s = getFromArrayList(m->updates, i);
    removeSimplexFromMesh(m,s);
  }
}
