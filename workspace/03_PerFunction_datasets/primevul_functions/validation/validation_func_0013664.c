static apr_table_t* oidc_request_state(request_rec *rr) {


	request_rec *r = (rr->main != NULL) ? rr->main : rr;


	apr_table_t *state = NULL;
	apr_pool_userdata_get((void**) &state, OIDC_USERDATA_KEY, r->pool);


	if (state == NULL) {
		state = apr_table_make(r->pool, 5);
		apr_pool_userdata_set(state, OIDC_USERDATA_KEY, NULL, r->pool);
	}


	return state;
}
