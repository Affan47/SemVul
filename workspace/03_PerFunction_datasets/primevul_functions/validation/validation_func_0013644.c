static apr_byte_t oidc_refresh_claims_from_userinfo_endpoint(request_rec *r,
		oidc_cfg *cfg, oidc_session_t *session) {

	oidc_provider_t *provider = NULL;
	const char *claims = NULL;
	const char *access_token = NULL;
	char *userinfo_jwt = NULL;


	if (oidc_get_provider_from_session(r, cfg, session, &provider) == FALSE)
		return FALSE;


	apr_time_t interval = apr_time_from_sec(
			provider->userinfo_refresh_interval);

	oidc_debug(r, "userinfo_endpoint=%s, interval=%d",
			provider->userinfo_endpoint_url,
			provider->userinfo_refresh_interval);

	if ((provider->userinfo_endpoint_url != NULL) && (interval > 0)) {


		apr_time_t last_refresh = oidc_session_get_userinfo_last_refresh(r,
				session);

		oidc_debug(r, "refresh needed in: %" APR_TIME_T_FMT " seconds",
				apr_time_sec(last_refresh + interval - apr_time_now()));


		if (last_refresh + interval < apr_time_now()) {


			access_token = oidc_session_get_access_token(r, session);


			claims = oidc_retrieve_claims_from_userinfo_endpoint(r, cfg,
					provider, access_token, session, NULL, &userinfo_jwt);


			oidc_store_userinfo_claims(r, cfg, session, provider, claims,
					userinfo_jwt);


			return TRUE;
		}
	}
	return FALSE;
}
