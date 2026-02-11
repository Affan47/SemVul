free_all_trans(tree* t)
{
  long i;

  for ( i = 0; i < nonodes2; i++ )
    t->freetrans[i] = i;
  t->transindex = nonodes2 - 1;
}
