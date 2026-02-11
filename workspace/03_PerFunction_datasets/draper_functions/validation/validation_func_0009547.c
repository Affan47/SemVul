nc_next_giter(ncgiter_t *iterp, int *grpidp) {
    int stat = NC_NOERR;
    int numgrps;
    int *grpids;
    int i;

    if(gs_empty(iterp)) {
	*grpidp = 0;
    } else {
	*grpidp = gs_pop(iterp);
	NC_CHECK(nc_inq_grps2(*grpidp, &numgrps, NULL));
	if(numgrps > 0) {
	    grpids = (int *)emalloc(sizeof(int) * numgrps);
	    NC_CHECK(nc_inq_grps2(*grpidp, &numgrps, grpids));
	    for(i = numgrps - 1; i >= 0; i--) {
		gs_push(iterp, grpids[i]);
	    }
	    free(grpids);
	}
    }
    return stat;
}
