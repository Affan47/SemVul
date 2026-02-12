authz_status oidc_authz_checker(request_rec *r, const char *require_args,
		const void *parsed_require_args,
		oidc_authz_match_claim_fn_type match_claim_fn) {

	oidc_debug(r, "enter: require_args=\"%s\"", require_args);


	if (r->user != NULL && strlen(r->user) == 0) {
		r->user = NULL;
		if (oidc_dir_cfg_unauth_action(r) == OIDC_UNAUTH_PASS)
			return AUTHZ_GRANTED;
		if (oidc_request_state_get(r, OIDC_REQUEST_STATE_KEY_DISCOVERY) != NULL)
			return AUTHZ_GRANTED;
	}


	json_t *claims = NULL, *id_token = NULL;
	oidc_authz_get_claims_and_idtoken(r, &claims, &id_token);


	if (claims)
		oidc_util_json_merge(r, id_token, claims);


	authz_status rc = oidc_authz_worker24(r, claims ? claims : id_token,
			require_args, parsed_require_args, match_claim_fn);


	if (claims)
		json_decref(claims);
	if (id_token)
		json_decref(id_token);

	if ((rc == AUTHZ_DENIED) && ap_auth_type(r))
		rc = oidc_handle_unauthorized_user24(r);

	return rc;
}
