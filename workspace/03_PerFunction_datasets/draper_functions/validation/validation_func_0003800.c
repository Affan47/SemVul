ldns_resolver_new_frm_file(ldns_resolver **res, const char *filename)
{
	ldns_resolver *r;
	FILE *fp;
	ldns_status s;

	if (!filename) {
		fp = fopen(LDNS_RESOLV_CONF, "r");

	} else {
		fp = fopen(filename, "r");
	}
	if (!fp) {
		return LDNS_STATUS_FILE_ERR;
	}

	s = ldns_resolver_new_frm_fp(&r, fp);
	fclose(fp);
	if (s == LDNS_STATUS_OK) {
		if (res) {
			*res = r;
			return LDNS_STATUS_OK;
		} else  {
			ldns_resolver_free(r);
			return LDNS_STATUS_NULL;
		}
	}
	return s;
}
