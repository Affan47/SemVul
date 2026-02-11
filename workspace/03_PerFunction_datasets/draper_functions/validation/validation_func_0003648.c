t_dns_name_towire_x(const char *testfile, size_t buflen) {
	int		line;
	int		cnt;
	int		result;
	unsigned int	dc_method;
	isc_result_t	exp_result;
	size_t		exp_data_len;
	char		*p;
	FILE		*fp;

	result = T_UNRESOLVED;
	fp = fopen(testfile, "r");
	if (fp != NULL) {
		line = 0;
		while ((p = t_fgetbs(fp)) != NULL) {

			++line;


			if ((isspace((unsigned char)*p)) || (*p == '#')) {
				(void)free(p);
				continue;
			}

			cnt = bustline(p, Tokens);
			if (cnt == 5) {


				dc_method = t_dc_method_fromtext(Tokens[3]);
				exp_result = t_dns_result_fromtext(Tokens[4]);
				exp_data_len = strtoul(Tokens[3], NULL, 10);

				result = test_dns_name_towire(Tokens[0],
							      dc_method,
							      Tokens[2],
							      exp_data_len,
							      exp_result,
							      buflen);
			} else {
				t_info("bad format at line %d\n", line);
			}

			(void)free(p);
			t_result(result);
		}
		(void)fclose(fp);
	} else {
		t_info("Missing datafile %s\n", testfile);
		t_result(result);
	}
}
