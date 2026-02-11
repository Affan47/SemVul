gabufr_replicate(gabufr_parseinf * inf, gaint numdesc, gaint numreps) {
  gaint i, z, nestedrep;
  gabufr_varid * base, * pos, * end, ** pos_addr;

  if (GABUFR_DEBUG) printf("**** replicating %d descriptors %d times\n",
			   numdesc, numreps);


  if (inf->descpos->next) {
    if (GABUFR_DEBUG) printf("using descpos (currently %p)\n", inf->descpos);
    pos_addr = &inf->descpos;
  } else {
    if (GABUFR_DEBUG) printf("using parentpos (currently %p)\n", inf->descpos);
    pos_addr = &inf->parentpos;
  }

  pos = base = (*pos_addr);
  for (i = 0; i < numdesc; i++) {
      pos = pos->next;
      if (!pos) {
	printf("error: ran out of descriptors to replicate!\n");
	return GABUFR_ERR;
      }
  }
  end = pos;

  nestedrep = (inf->z >= 0);
  if (nestedrep) {

    if (GABUFR_DEBUG) printf("warning: nested replication in dataset\n");
  }

  for (z = 0; z < numreps; z++) {
    if (GABUFR_DEBUG) printf("\n** rep = %d of %d\n", z, numreps);


    (*pos_addr) = base;

    if (!nestedrep) {
      inf->z = z;
    }

    while ((*pos_addr) != end) {
      (*pos_addr) = (*pos_addr)->next;
      if (GABUFR_DEBUG) printf("descpos=%d-%d-%d\n",
			       (*pos_addr)->f, (*pos_addr)->x, (*pos_addr)->y);
      if (gabufr_parsedesc(inf, (*pos_addr)->f, (*pos_addr)->x,
			   (*pos_addr)->y) == GABUFR_ERR) {
	return GABUFR_ERR;
      }
    }
  }

  if (!nestedrep) {
    inf->z = -1;
  }


  (*pos_addr) = end;

  if (GABUFR_DEBUG) printf("**** done replicating %d descriptors %d times\n\n",
			   numdesc, numreps);
  return GABUFR_OK;
}
