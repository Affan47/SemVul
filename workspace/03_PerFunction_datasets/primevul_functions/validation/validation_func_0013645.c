int oidc_check_user_id(request_rec *r) {

	oidc_cfg *c = ap_get_module_config(r->server->module_config,
			&auth_openidc_module);


	oidc_debug(r, "incoming request: \"%s?%s\", ap_is_initial_req(r)=%d",
			r->parsed_uri.path, r->args, ap_is_initial_req(r));


	const char *current_auth = ap_auth_type(r);
	if (current_auth == NULL)
		return DECLINED;


	if (strcasecmp(current_auth, OIDC_AUTH_TYPE_OPENID_CONNECT) == 0) {

		r->ap_auth_type = (char*) current_auth;
		return oidc_check_userid_openidc(r, c);
	}


	if (strcasecmp(current_auth, OIDC_AUTH_TYPE_OPENID_OAUTH20) == 0) {

		r->ap_auth_type = (char*) current_auth;
		return oidc_oauth_check_userid(r, c, NULL);
	}


	if (strcasecmp(current_auth, OIDC_AUTH_TYPE_OPENID_BOTH) == 0)
		return oidc_check_mixed_userid_oauth(r, c);


	return DECLINED;
}
