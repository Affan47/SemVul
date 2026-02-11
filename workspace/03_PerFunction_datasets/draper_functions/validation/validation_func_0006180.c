write_elists(
scanrd_ *s
) {
	char *fname = s->refname;
	FILE *elf;
	int i;

	if ((elf=fopen(fname,"w"))==NULL) {
		s->errv = SI_REF_WRITE_ERR;
		sprintf(s->errm,"write_elists: error opening match reference file '%s'",fname);
		return 1;
	}

	fprintf(elf,"REF_ROTATION %f\n\n",DEG(s->irot));

	fprintf(elf,"XLIST %d\n",s->xelist.c);
	for (i = 0; i < s->xelist.c; i++)
		fprintf(elf,"  %f %f %f\n",s->xelist.a[i].pos, s->xelist.a[i].len, s->xelist.a[i].ccount);
	fprintf(elf,"\n");

	fprintf(elf,"YLIST %d\n",s->yelist.c);
	for (i = 0; i < s->yelist.c; i++)
		fprintf(elf,"  %f %f %f\n",s->yelist.a[i].pos, s->yelist.a[i].len, s->yelist.a[i].ccount);
	fprintf(elf,"\n");

	if ((fclose(elf)) == EOF) {
		s->errv = SI_REF_WRITE_ERR;
		error("write_elists: Unable to close match reference file '%s'\n",fname);
		return 1;
	}
	return 0;
}
