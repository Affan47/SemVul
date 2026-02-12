const char* oidc_request_state_get(request_rec *r, const char *key) {


	apr_table_t *state = oidc_request_state(r);


	return apr_table_get(state, key);
}
