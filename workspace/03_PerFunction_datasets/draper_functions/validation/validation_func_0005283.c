zWriteTransition (FILE *stream, const zTransition *t, int iso_groups) {
	int i;
	(void)fprintf(stream, "%s\t%s\t%f", zStrIdx2Char(t->from),
				  zStrIdx2Char(t->to), t->prob[0]);
	for(i = 1; i < iso_groups; i++){
		(void) fprintf(stream, "\t%f", t->prob[i]);
	}
	(void) fprintf(stream, "\n");
}
