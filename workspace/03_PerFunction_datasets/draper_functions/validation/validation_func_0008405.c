molring(int n, char *cbuf)
{
  int *list = (int *) cbuf;
  int *dlist = cptr->dlist;
  std::map<int,int> *hash = cptr->hash;
  int nlocal = cptr->atom->nlocal;
  int *molecule = cptr->atom->molecule;

  hash->clear();
  for (int i = 0; i < n; i++) (*hash)[list[i]] = 1;

  for (int i = 0; i < nlocal; i++)
    if (hash->find(molecule[i]) != hash->end()) dlist[i] = 1;
}
