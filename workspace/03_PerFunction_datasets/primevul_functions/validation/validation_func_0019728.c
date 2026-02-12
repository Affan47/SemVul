static int oidc_handle_existing_session(request_rec *r, oidc_cfg *cfg,
		oidc_session_t *session) {

	oidc_debug(r, "enter");


	apr_byte_t needs_save = FALSE;


	r->user = apr_pstrdup(r->pool, session->remote_user);
	oidc_debug(r, "set remote_user to \"%s\"", r->user);


	char *authn_header = oidc_cfg_dir_authn_header(r);
	apr_byte_t pass_headers = oidc_cfg_dir_pass_info_in_headers(r);
	apr_byte_t pass_envvars = oidc_cfg_dir_pass_info_in_envvars(r);


	if (oidc_check_cookie_domain(r, cfg, session) == FALSE)
		return HTTP_UNAUTHORIZED;


	int rc = oidc_check_max_session_duration(r, cfg, session);
	if (rc != OK)
		return rc;


	needs_save = oidc_refresh_access_token_before_expiry(r, cfg, session,
			oidc_cfg_dir_refresh_access_token_before_expiry(r),
			oidc_cfg_dir_logout_on_error_refresh(r));
	if (needs_save == ERROR)
		return oidc_handle_logout_request(r, cfg, session, cfg->default_slo_url);


	if (oidc_refresh_claims_from_userinfo_endpoint(r, cfg, session) == TRUE)
		needs_save = TRUE;


	oidc_scrub_headers(r);


	if ((r->user != NULL) && (authn_header != NULL))
		oidc_util_hdr_in_set(r, authn_header, r->user);

	const char *s_claims = NULL;
	const char *s_id_token = NULL;


	oidc_copy_tokens_to_request_state(r, session, &s_id_token, &s_claims);

	if ((cfg->pass_userinfo_as & OIDC_PASS_USERINFO_AS_CLAIMS)) {

		if (oidc_set_app_claims(r, cfg, session, s_claims) == FALSE)
			return HTTP_INTERNAL_SERVER_ERROR;
	}

	if ((cfg->pass_userinfo_as & OIDC_PASS_USERINFO_AS_JSON_OBJECT)) {

		oidc_util_set_app_info(r, OIDC_APP_INFO_USERINFO_JSON, s_claims,
				OIDC_DEFAULT_HEADER_PREFIX, pass_headers, pass_envvars);
	}

	if ((cfg->pass_userinfo_as & OIDC_PASS_USERINFO_AS_JWT)) {
		if (cfg->session_type != OIDC_SESSION_TYPE_CLIENT_COOKIE) {

			const char *s_userinfo_jwt = oidc_session_get_userinfo_jwt(r,
					session);
			if (s_userinfo_jwt != NULL) {

				oidc_util_set_app_info(r, OIDC_APP_INFO_USERINFO_JWT,
						s_userinfo_jwt,
						OIDC_DEFAULT_HEADER_PREFIX, pass_headers, pass_envvars);
			} else {
				oidc_debug(r,
						"configured to pass userinfo in a JWT, but no such JWT was found in the session (probably no such JWT was returned from the userinfo endpoint)");
			}
		} else {
			oidc_error(r,
					"session type \"client-cookie\" does not allow storing/passing a userinfo JWT; use \"" OIDCSessionType " server-cache\" for that");
		}
	}

	if ((cfg->pass_idtoken_as & OIDC_PASS_IDTOKEN_AS_CLAIMS)) {

		if (oidc_set_app_claims(r, cfg, session, s_id_token) == FALSE)
			return HTTP_INTERNAL_SERVER_ERROR;
	}

	if ((cfg->pass_idtoken_as & OIDC_PASS_IDTOKEN_AS_PAYLOAD)) {

		oidc_util_set_app_info(r, OIDC_APP_INFO_ID_TOKEN_PAYLOAD, s_id_token,
				OIDC_DEFAULT_HEADER_PREFIX, pass_headers, pass_envvars);
	}

	if ((cfg->pass_idtoken_as & OIDC_PASS_IDTOKEN_AS_SERIALIZED)) {
		if (cfg->session_type != OIDC_SESSION_TYPE_CLIENT_COOKIE) {

			const char *s_id_token = oidc_session_get_idtoken(r, session);

			oidc_util_set_app_info(r, OIDC_APP_INFO_ID_TOKEN, s_id_token,
					OIDC_DEFAULT_HEADER_PREFIX, pass_headers, pass_envvars);
		} else {
			oidc_error(r,
					"session type \"client-cookie\" does not allow storing/passing the id_token; use \"" OIDCSessionType " server-cache\" for that");
		}
	}


	if (oidc_session_pass_tokens_and_save(r, cfg, session, needs_save) == FALSE)
		return HTTP_INTERNAL_SERVER_ERROR;


	return OK;
}
