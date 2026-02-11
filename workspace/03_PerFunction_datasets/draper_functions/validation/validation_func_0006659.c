data_body(int m, int ninteger, int ndouble,
                             char **ivalues, char **dvalues)
{
  if (body[m]) error->one(FLERR,"Assigning body parameters to non-body atom");
  if (nlocal_bonus == nmax_bonus) grow_bonus();
  bptr->data_body(nlocal_bonus,ninteger,ndouble,ivalues,dvalues);
  bonus[nlocal_bonus].ilocal = m;
  body[m] = nlocal_bonus++;
}
