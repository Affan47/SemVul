ss_filter_keys (indexer_t* ix, struct berval** values)


{
    auto struct berval** keys = NULL;
    if (values != NULL) {
	auto size_t n;
	auto struct berval** val;
	for (n=0,val=values; *val != NULL; ++n,++val);
	keys = (struct berval**) slapi_ch_malloc ((n+1) * sizeof (struct berval*));
	for (n=0,val=values; *val != NULL; ++n,++val) {
	    keys[n] = ss_filter_key (ix, *val);
	}
	keys[n] = NULL;
    }
    return keys;
}
