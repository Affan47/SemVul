lnstat_dump(FILE *outfd, struct lnstat_file *lnstat_files)
{
	struct lnstat_file *lf;

	for (lf = lnstat_files; lf; lf = lf->next) {
		int i;

		fprintf(outfd, "%s:\n", lf->path);

		for (i = 0; i < lf->num_fields; i++)
			fprintf(outfd, "\t%2u: %s\n", i+1, lf->fields[i].name);

	}
	return 0;
}
