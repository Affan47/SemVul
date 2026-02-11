reallocsites(void)
{


  long i;

  for (i = 0; i < spp; i++) {
    free(y[i]);
    y[i] = (Char *)Malloc(sites*sizeof(Char));
  }
  free(category);
  free(oldweight);
  free(weight);
  free(alias);
  free(ally);
  free(location);
  free(weightrat);

  category = (steptr)Malloc(sites*sizeof(long));
  oldweight = (steptr)Malloc(sites*sizeof(long));
  weight = (steptr)Malloc(sites*sizeof(long));
  alias = (steptr)Malloc(sites*sizeof(long));
  ally = (steptr)Malloc(sites*sizeof(long));
  location = (steptr)Malloc(sites*sizeof(long));
  weightrat = (double *)Malloc(sites*sizeof(double));
}
