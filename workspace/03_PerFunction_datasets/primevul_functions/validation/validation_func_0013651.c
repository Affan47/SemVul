static void oidc_store_userinfo_claims(request_rec *r, oidc_cfg *c,
		oidc_session_t *session, oidc_provider_t *provider, const char *claims,
		const char *userinfo_jwt) {

	oidc_debug(r, "enter");


	if (claims != NULL) {


		oidc_session_set_userinfo_claims(r, session, claims);

		if (c->session_type != OIDC_SESSION_TYPE_CLIENT_COOKIE) {

			oidc_session_set_userinfo_jwt(r, session, userinfo_jwt);
		}

	} else {


		oidc_session_set_userinfo_claims(r, session, NULL);

		oidc_session_set_userinfo_jwt(r, session, NULL);
	}


	if (provider->userinfo_refresh_interval > 0)
		oidc_session_reset_userinfo_last_refresh(r, session);
}
