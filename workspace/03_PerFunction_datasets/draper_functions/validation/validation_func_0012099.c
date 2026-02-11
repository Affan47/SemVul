rbt_init(char *filename, dns_rbt_t **rbt, isc_mem_t *mctx) {
	int		rval;
	isc_result_t	dns_result;
	char		*p;
	FILE		*fp;

	fp = fopen(filename, "r");
	if (fp == NULL) {
		t_info("No such file %s\n", filename);
		return(1);
	}

	dns_result = dns_rbt_create(mctx, delete_name, mctx, rbt);
	if (dns_result != ISC_R_SUCCESS) {
		t_info("dns_rbt_create failed %s\n",
				dns_result_totext(dns_result));
		fclose(fp);
		return(1);
	}

	while ((p = t_fgetbs(fp)) != NULL) {


		if ((*p == '#') || (*p == '\0') || (*p == ' ')) {
			(void)free(p);
			continue;
		}

		if (T_debug)
			t_info("adding name %s to the rbt\n", p);

		rval = t1_add(p, *rbt, mctx, &dns_result);
		if ((rval != 0) || (dns_result != ISC_R_SUCCESS)) {
			t_info("add of %s failed\n", p);
			dns_rbt_destroy(rbt);
			fclose(fp);
			return(1);
		}
		(void) free(p);
	}
	fclose(fp);
	return(0);
}
