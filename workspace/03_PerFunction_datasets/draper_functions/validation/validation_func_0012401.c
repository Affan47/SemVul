print_one_if(FILE *fp, const struct ifstat_ent *n,
			 const unsigned long long *vals)
{
	int i;

	fprintf(fp, "%-15s ", n->name);
	for (i=0; i<4; i++)
		format_rate(fp, vals, n->rate, i);
	fprintf(fp, "\n");

	if (!show_errors) {
		fprintf(fp, "%-15s ", "");
		format_pair(fp, vals, 4, 6);
		format_pair(fp, vals, 5, 7);
		format_rate(fp, vals, n->rate, 11);
		format_rate(fp, vals, n->rate, 9);
		fprintf(fp, "\n");
	} else {
		fprintf(fp, "%-15s ", "");
		format_rate(fp, vals, n->rate, 4);
		format_rate(fp, vals, n->rate, 6);
		format_rate(fp, vals, n->rate, 11);
		format_rate(fp, vals, n->rate, 10);
		fprintf(fp, "\n");

		fprintf(fp, "%-15s ", "");
		format_rate(fp, vals, n->rate, 12);
		format_rate(fp, vals, n->rate, 13);
		format_rate(fp, vals, n->rate, 14);
		format_rate(fp, vals, n->rate, 15);
		fprintf(fp, "\n");

		fprintf(fp, "%-15s ", "");
		format_rate(fp, vals, n->rate, 5);
		format_rate(fp, vals, n->rate, 7);
		format_rate(fp, vals, n->rate, 9);
		format_rate(fp, vals, n->rate, 17);
		fprintf(fp, "\n");

		fprintf(fp, "%-15s ", "");
		format_rate(fp, vals, n->rate, 16);
		format_rate(fp, vals, n->rate, 18);
		format_rate(fp, vals, n->rate, 19);
		format_rate(fp, vals, n->rate, 20);
		fprintf(fp, "\n");
	}
}
