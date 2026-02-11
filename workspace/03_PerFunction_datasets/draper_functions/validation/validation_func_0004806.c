IIT_create_div_header (T new, int total_nintervals, int ntypes, int nfields, int ndivs,
		       int *nintervals, int *nnodes, int *cum_nintervals, int *cum_nnodes,
		       List_T divlist, Sorttype_T divsort, int version) {
  int divno;
  unsigned int pointer = 0U;
  List_T p;
  char *divstring;
  int stringlen, k;

  new->version = version;
  new->total_nintervals = total_nintervals;
  new->ntypes = ntypes;
  new->nfields = nfields;

  new->ndivs = ndivs;
  new->nintervals = (int *) CALLOC(new->ndivs,sizeof(int));
  for (divno = 0; divno < ndivs; divno++) {
    new->nintervals[divno] = nintervals[divno];
  }

  new->cum_nintervals = (int *) CALLOC(new->ndivs+1,sizeof(int));
  for (divno = 0; divno <= ndivs; divno++) {
    new->cum_nintervals[divno] = cum_nintervals[divno];
  }

  new->nnodes = (int *) CALLOC(new->ndivs,sizeof(int));
  for (divno = 0; divno < ndivs; divno++) {
    new->nnodes[divno] = nnodes[divno];
  }

  new->cum_nnodes = (int *) CALLOC(new->ndivs+1,sizeof(int));
  for (divno = 0; divno <= ndivs; divno++) {
    new->cum_nnodes[divno] = cum_nnodes[divno];
  }

  new->divsort = divsort;

  new->divpointers = (unsigned int *) CALLOC(new->ndivs+1,sizeof(unsigned int));

  k = 0;
  new->divpointers[k++] = pointer = 0U;
  for (p = divlist; p != NULL; p = List_next(p)) {
    divstring = (char *) List_head(p);
    pointer += (unsigned int) strlen(divstring)+1U;
    new->divpointers[k++] = pointer;
  }

  stringlen = new->divpointers[new->ndivs];
  new->divstrings = (char *) CALLOC(stringlen,sizeof(char));

  k = 0;
  for (p = divlist; p != NULL; p = List_next(p)) {
    divstring = (char *) List_head(p);
    strcpy(&(new->divstrings[k]),divstring);
    k += strlen(divstring);
    new->divstrings[k++] = '\0';
  }

  return;
}
