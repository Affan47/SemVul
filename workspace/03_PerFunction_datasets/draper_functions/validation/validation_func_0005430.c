Hash_Find(char *tbl, long key)
{
  int tbl_size = Tbl_Size(tbl);
  HashNode *t = Hsh_Table(tbl);
  HashNode *prev;
  HashNode p;

  prev = Hash_Locate(t, tbl_size, key);
  p = *prev;

  if (p == NULL)
    return NULL;

  return (char *) (&(p->key));
}
