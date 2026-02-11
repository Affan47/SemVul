selfont(int back)
{
	char *p;
	int flags;

	if (gcur.font_n[0] == '\0')
		return;
	flags = 0;
	p = strchr(gcur.font_n, '-');
	if (p == 0) {
		fprintf(fout, " font-family=\"%s\" font-size=\"%.2f\"",
			gcur.font_n, gcur.font_s);
	} else {
		fprintf(fout, " font-family=\"%.*s\" font-size=\"%.2f\"",
			(int) (p - gcur.font_n), gcur.font_n, gcur.font_s);
		if (strstr(gcur.font_n, "Bold") != 0) {
			fprintf(fout, " font-weight=\"bold\"");
			flags = 1;
		}
		if (strstr(gcur.font_n, "Italic") != 0) {
			fprintf(fout, " font-style=\"italic\"");
			flags |= 2;
		} else if (strstr(gcur.font_n, "Oblique") != 0) {
			fprintf(fout, " font-style=\"oblique\"");
			flags |= 2;
		}
	}
	if (!back)
		return;
	if (!(flags & 1)
	 && strstr(gold.font_n, "Bold") != 0)
		fprintf(fout, " font-weight=\"normal\"");
	if (!(flags & 2)
	 && (strstr(gold.font_n, "Italic") != 0
	  || strstr(gold.font_n, "Oblique") != 0))
		fprintf(fout, " font-style=\"normal\"");
}
