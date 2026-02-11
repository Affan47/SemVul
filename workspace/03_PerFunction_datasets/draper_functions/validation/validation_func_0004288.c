save_cylinder_info(FILE *f, struct dive *dive)
{
	int i;

	for (i = 0; i < MAX_CYLINDERS; i++) {
		cylinder_t *cylinder = dive->cylinder+i;
		int volume = cylinder->type.size.mliter;
		const char *description = cylinder->type.description;
		int o2 = cylinder->gasmix.o2.permille;
		int he = cylinder->gasmix.he.permille;


		if (!o2 && !volume)
			return;
		fprintf(f, "  <cylinder");
		if (o2) {
			fprintf(f, " o2='%u.%u%%'", FRACTION(o2, 10));
			if (he)
				fprintf(f, " he='%u.%u%%'", FRACTION(he, 10));
		}
		if (volume)
			show_milli(f, " size='", volume, " l", "'");
		if (description)
			fprintf(f, " description='%s'", description);
		fprintf(f, " />\n");
	}
}
