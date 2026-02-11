json_print_pwr_in_stats(struct activity *a, int curr, int tab,
					unsigned long long itv)
{
	int i;
	struct stats_pwr_in *spc;
	int sep = FALSE;

	if (!IS_SELECTED(a->options) || (a->nr <= 0))
		goto close_json_markup;

	json_markup_power_management(tab, OPEN_JSON_MARKUP);
	tab++;

	xprintf(tab++, "\"voltage-input\": [");

	for (i = 0; i < a->nr; i++) {
		spc = (struct stats_pwr_in *) ((char *) a->buf[curr]  + i * a->msize);

		if (sep) {
			printf(",\n");
		}
		sep = TRUE;

		xprintf0(tab, "{\"number\": %d, "
			 "\"inV\": %.2f, "
			 "\"percent-in\": %.2f, "
			 "\"device\": \"%s\"}",
			 i,
			 spc->in,
			 (spc->in_max - spc->in_min) ?
			 (spc->in - spc->in_min) / (spc->in_max - spc->in_min) * 100 :
			 0.0,
			 spc->device);
	}

	printf("\n");
	xprintf0(--tab, "]");
	tab--;

close_json_markup:
	if (CLOSE_MARKUP(a->options)) {
		json_markup_power_management(tab, CLOSE_JSON_MARKUP);
	}
}
