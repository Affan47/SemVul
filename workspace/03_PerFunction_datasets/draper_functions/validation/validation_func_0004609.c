ascii_header_output(SpiceStream *sf, int *indices, int nidx)
{
	int i, j;
	char buf[1024];

	if((sf->nsweepparam > 0) && (sweep_mode == SWEEP_PREPEND)) {
		for(i = 0; i < sf->nsweepparam; i++) {
			printf("%s ", sf->spar[i].name);
		}
	}
	for(i = 0; i < nidx; i++) {
		if(i > 0)
			putchar(' ');
		if(indices[i] == 0) {
			ss_var_name(sf->ivar, 0, buf, 1024);
			printf("%s", buf);
		} else {
			int varno = indices[i]-1;
			for(j = 0; j < sf->dvar[varno].ncols; j++) {
				if(j > 0)
					putchar(' ');
				ss_var_name(&sf->dvar[varno], j, buf, 1024);
				printf("%s", buf);
			}
		}
	}
	putchar('\n');
}
