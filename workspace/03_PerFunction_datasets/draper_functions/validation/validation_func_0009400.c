ef(I arg)
{
  E epr;
  if(!QE(arg)){dc((A)arg);R;}
  epr=XE(arg);
  DO(epr->n,ef(epr->a[i]));
  ef(epr->f);
  mf((I *)epr);
}
