qh_settruncate (setT *set, int size) {

  if (size < 0 || size > (int)set->maxsize) qhull_fatal(19);

  set->e[set->maxsize]= (void *) (size+1);
  set->e[size]= NULL;
}
