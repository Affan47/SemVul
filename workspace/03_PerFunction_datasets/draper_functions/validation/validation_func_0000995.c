update_full_data_values (const DATASET *dset)
{
    int i, s, t;

#if SUBDEBUG
    fprintf(stderr, "update_full_data_values: fullset->Z=%p, dset->Z=%p, dset=%p\n",
	    (void *) fullset->Z, (void *) dset->Z, (void *) dset);
#endif

    for (i=1; i<fullset->v && i<dset->v; i++) {
	s = 0;
	for (t=0; t<fullset->n; t++) {
	    if (dset->submask[t] == 1) {
		fullset->Z[i][t] = dset->Z[i][s++];
	    } else if (dset->submask[t] == 'p') {

		s++;
	    }
	}
    }
}
