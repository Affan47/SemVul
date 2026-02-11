om_html_print_numkey_entry(FILE *fp, char *key, int val, char *link,
		int num)
{
	fprintf(fp, "<tr><td align=\"left\" class=\"keyentry\">");
	fprintf(fp, "%d)", num);
	fprintf(fp, "<td align=\"left\" class=\"valueentry\">");
	fprintf(fp, "%d", val);
	fprintf(fp, "</td><td align=\"left\" class=\"keyentry\">");
	if (link != NULL) {
		fprintf(fp, "<a class=\"url\" href=\"%s\">", link);
		om_html_entities(fp, key);
		fprintf(fp, "</a>");
	} else if (!strncmp(key, "http://", 7)) {
		fprintf(fp, "<a class=\"url\" href=\"%s\">", key);
		om_html_entities(fp, key);
		fprintf(fp, "</a>");
	} else {
		om_html_entities(fp, key);
	}
	fprintf(fp, "</td></tr>\n");
}
