static void oidc_scrub_request_headers(request_rec *r, const char *claim_prefix,
		apr_hash_t *scrub) {

	const int prefix_len = claim_prefix ? strlen(claim_prefix) : 0;


	const apr_array_header_t *const h = apr_table_elts(r->headers_in);


	apr_table_t *clean_headers = apr_table_make(r->pool, h->nelts);


	const apr_table_entry_t *const e = (const apr_table_entry_t*) h->elts;
	int i;
	for (i = 0; i < h->nelts; i++) {
		const char *const k = e[i].key;


		const char *hdr =
				(k != NULL) && (scrub != NULL) ?
						apr_hash_get(scrub, k, APR_HASH_KEY_STRING) : NULL;
		const int header_matches = (hdr != NULL)
						&& (oidc_strnenvcmp(k, hdr, -1) == 0);


		const int prefix_matches = (k != NULL) && prefix_len
				&& (oidc_strnenvcmp(k, claim_prefix, prefix_len) == 0);


		if (!prefix_matches && !header_matches) {
			apr_table_addn(clean_headers, k, e[i].val);
		} else {
			oidc_warn(r, "scrubbed suspicious request header (%s: %.32s)", k,
					e[i].val);
		}
	}


	r->headers_in = clean_headers;
}
