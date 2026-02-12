void oidc_request_state_set(request_rec *r, const char *key, const char *value) {


	apr_table_t *state = oidc_request_state(r);


	apr_table_set(state, key, value);
}
