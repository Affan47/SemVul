static apr_byte_t oidc_refresh_access_token(request_rec *r, oidc_cfg *c,
		oidc_session_t *session, oidc_provider_t *provider,
		char **new_access_token) {

	oidc_debug(r, "enter");


	const char *refresh_token = oidc_session_get_refresh_token(r, session);
	if (refresh_token == NULL) {
		oidc_warn(r,
				"refresh token routine called but no refresh_token found in the session");
		return FALSE;
	}


	char *s_id_token = NULL;
	int expires_in = -1;
	char *s_token_type = NULL;
	char *s_access_token = NULL;
	char *s_refresh_token = NULL;


	if (oidc_proto_refresh_request(r, c, provider, refresh_token, &s_id_token,
			&s_access_token, &s_token_type, &expires_in, &s_refresh_token)
			== FALSE) {
		oidc_error(r, "access_token could not be refreshed");
		return FALSE;
	}


	oidc_session_set_access_token(r, session, s_access_token);
	oidc_session_set_access_token_expires(r, session, expires_in);


	oidc_session_reset_access_token_last_refresh(r, session);


	if (new_access_token != NULL)
		*new_access_token = s_access_token;


	if (s_refresh_token != NULL)
		oidc_session_set_refresh_token(r, session, s_refresh_token);


	if (s_id_token != NULL) {

		if (c->session_type != OIDC_SESSION_TYPE_CLIENT_COOKIE)
			oidc_session_set_idtoken(r, session, s_id_token);

		oidc_jwt_t *id_token_jwt = NULL;
		oidc_jose_error_t err;
		if (oidc_jwt_parse(r->pool, s_id_token, &id_token_jwt, NULL, &err) == TRUE) {


			oidc_session_set_idtoken_claims(r, session,
				id_token_jwt->payload.value.str);

			if (provider->session_max_duration == 0) {

				apr_time_t session_expires = apr_time_from_sec(id_token_jwt->payload.exp);
				oidc_session_set_session_expires(r, session, session_expires);


				oidc_log_session_expires(r, "session max lifetime", session_expires);
			}
		} else {
			oidc_warn(r, "parsing of id_token failed");
		}
	}

	return TRUE;
}
