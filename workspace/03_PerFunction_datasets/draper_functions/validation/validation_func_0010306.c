slapi_rdn_get_size(Slapi_RDN *srdn)
{
	size_t sz = 0;
	char **ptr;

	if (!srdn) {
		goto bail;
	}
	sz = sizeof(Slapi_RDN);
	if (srdn->rdn) {
		sz += strlen(srdn->rdn) + 1;
	}
	if (srdn->nrdn) {
		sz += strlen(srdn->nrdn) + 1;
	}
	if (srdn->rdns) {
		for (ptr = srdn->rdns; ptr && *ptr; ptr++) {
			sz += strlen(*ptr) + 1;
		}
	}
	if (srdn->all_rdns) {
		for (ptr = srdn->all_rdns; ptr && *ptr; ptr++) {
			sz += strlen(*ptr) + 1;
		}
	}
	if (srdn->all_nrdns) {
		for (ptr = srdn->all_nrdns; ptr && *ptr; ptr++) {
			sz += strlen(*ptr) + 1;
		}
	}
bail:
	return sz;
}
