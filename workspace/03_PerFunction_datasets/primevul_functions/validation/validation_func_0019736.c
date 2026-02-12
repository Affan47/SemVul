static apr_byte_t oidc_session_pass_tokens_and_save(request_rec *r,
		oidc_cfg *cfg, oidc_session_t *session, apr_byte_t needs_save) {

	apr_byte_t pass_headers = oidc_cfg_dir_pass_info_in_headers(r);
	apr_byte_t pass_envvars = oidc_cfg_dir_pass_info_in_envvars(r);


	const char *refresh_token = oidc_session_get_refresh_token(r, session);
	if ((oidc_cfg_dir_pass_refresh_token(r) != 0) && (refresh_token != NULL)) {

		oidc_util_set_app_info(r, OIDC_APP_INFO_REFRESH_TOKEN, refresh_token,
				OIDC_DEFAULT_HEADER_PREFIX, pass_headers, pass_envvars);
	}


	const char *access_token = oidc_session_get_access_token(r, session);
	if (access_token != NULL) {

		oidc_util_set_app_info(r, OIDC_APP_INFO_ACCESS_TOKEN, access_token,
				OIDC_DEFAULT_HEADER_PREFIX, pass_headers, pass_envvars);
	}


	const char *access_token_expires = oidc_session_get_access_token_expires(r,
			session);
	if (access_token_expires != NULL) {

		oidc_util_set_app_info(r, OIDC_APP_INFO_ACCESS_TOKEN_EXP,
				access_token_expires,
				OIDC_DEFAULT_HEADER_PREFIX, pass_headers, pass_envvars);
	}


	apr_time_t interval = apr_time_from_sec(cfg->session_inactivity_timeout);
	apr_time_t now = apr_time_now();
	apr_time_t slack = interval / 10;
	if (slack > apr_time_from_sec(60))
		slack = apr_time_from_sec(60);
	if (session->expiry - now < interval - slack) {
		session->expiry = now + interval;
		needs_save = TRUE;
	}


	oidc_log_session_expires(r, "session inactivity timeout", session->expiry);


	if (needs_save)
		if (oidc_session_save(r, session, FALSE) == FALSE)
			return FALSE;

	return TRUE;
}
