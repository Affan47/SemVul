IIT_get_highs_for_low (int *nuniq, T this, int divno, unsigned int x) {
  unsigned int *uniq = NULL, *coords = NULL, prev;
  int neval, ncoords, i;
  int match, lambda, min1, max1 = 0;
  struct Interval_T interval;

  if (divno < 0) {

    *nuniq = 0;
    return (unsigned int *) NULL;
  }
  min1 = this->nintervals[divno] + 1;

  debug(printf("Entering IIT_get_highs_for_low with divno %d and query %u\n",divno,x));
  fnode_query_aux(&min1,&max1,this,divno,0,x);
  debug(printf("min1=%d max1=%d\n",min1,max1));

  if (max1 < min1) {
    *nuniq = 0;
    return (unsigned int *) NULL;
  } else {
    neval = (max1 - min1 + 1) + (max1 - min1 + 1);
    coords = (unsigned int *) CALLOC(neval,sizeof(unsigned int));
    ncoords = 0;

    for (lambda = min1; lambda <= max1; lambda++) {
      match = this->sigmas[divno][lambda];

      interval = this->intervals[divno][match - 1];
      if (interval.low == x) {
	coords[ncoords++] = interval.high;
      }

      match = this->omegas[divno][lambda];

      interval = this->intervals[divno][match - 1];
      if (interval.low == x) {
	coords[ncoords++] = interval.high;
      }
    }


    qsort(coords,ncoords,sizeof(unsigned int),uint_compare_ascending);

    uniq = (unsigned int *) CALLOC(ncoords,sizeof(unsigned int));
    *nuniq = 0;
    prev = 0;
    for (i = 0; i < ncoords; i++) {
      if (coords[i] != prev) {
	uniq[(*nuniq)++] = coords[i];
	prev = coords[i];
      }
    }

    FREE(coords);
    return uniq;
  }
}
