report_print_standard_section(const seaudit_log_t * log, const seaudit_report_t * report,
					 xmlChar * id, xmlChar * title, FILE * outfile)
{
	size_t sz, len, i;
	int rt = 0;

	if (!report_is_valid_section_name((char *)id)) {
		ERR(log, "%s", "Invalid standard section ID.");
		errno = EINVAL;
		return -1;
	}
	sz = strlen((char *)id);
	if (title != NULL) {
		if (report->format == SEAUDIT_REPORT_FORMAT_HTML) {
			fprintf(outfile, "<h2 class=\"standard_section_title\"><u>%s</h2></u>\n", title);
		} else {
			fprintf(outfile, "%s\n", title);
			len = strlen((char *)title);
			for (i = 0; i < len; i++) {
				fprintf(outfile, "-");
			}
			fprintf(outfile, "\n");
		}
	}
	if (strncasecmp((char *)id, "PolicyLoads", sz) == 0) {
		rt = report_print_policy_loads(log, report, outfile);
	} else if (strncasecmp((char *)id, "EnforcementToggles", sz) == 0) {
		rt = report_print_enforce_toggles(log, report, outfile);
	} else if (strncasecmp((char *)id, "PolicyBooleans", sz) == 0) {
		rt = report_print_policy_booleans(log, report, outfile);
	} else if (strncasecmp((char *)id, "AllowListing", sz) == 0) {
		rt = report_print_avc_listing(log, report, SEAUDIT_AVC_GRANTED, outfile);
	} else if (strncasecmp((char *)id, "DenyListing", sz) == 0) {
		rt = report_print_avc_listing(log, report, SEAUDIT_AVC_DENIED, outfile);
	} else if (strncasecmp((char *)id, "Statistics", sz) == 0) {
		rt = report_print_stats(log, report, outfile);
	}
	if (rt < 0) {
		return rt;
	}

	if (report->format == SEAUDIT_REPORT_FORMAT_HTML)
		fprintf(outfile, "<br>\n");
	else
		fprintf(outfile, "\n");

	return 0;
}
