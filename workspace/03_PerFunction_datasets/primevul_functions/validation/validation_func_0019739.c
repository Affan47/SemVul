static int oidc_handle_logout_backchannel(request_rec *r, oidc_cfg *cfg) {

	oidc_debug(r, "enter");

	const char *logout_token = NULL;
	oidc_jwt_t *jwt = NULL;
	oidc_jose_error_t err;
	oidc_jwk_t *jwk = NULL;
	oidc_provider_t *provider = NULL;
	char *sid = NULL, *uuid = NULL;
	oidc_session_t session;
	int rc = HTTP_BAD_REQUEST;

	apr_table_t *params = apr_table_make(r->pool, 8);
	if (oidc_util_read_post_params(r, params, FALSE, NULL) == FALSE) {
		oidc_error(r,
				"could not read POST-ed parameters to the logout endpoint");
		goto out;
	}

	logout_token = apr_table_get(params, OIDC_PROTO_LOGOUT_TOKEN);
	if (logout_token == NULL) {
		oidc_error(r,
				"backchannel lggout endpoint was called but could not find a parameter named \"%s\"",
				OIDC_PROTO_LOGOUT_TOKEN);
		goto out;
	}


	if (oidc_jwt_parse(r->pool, logout_token, &jwt,
			oidc_util_merge_symmetric_key(r->pool, cfg->private_keys, NULL),
			&err) == FALSE) {
		oidc_error(r, "oidc_jwt_parse failed: %s", oidc_jose_e2s(r->pool, err));
		goto out;
	}

	provider = oidc_get_provider_for_issuer(r, cfg, jwt->payload.iss, FALSE);
	if (provider == NULL) {
		oidc_error(r, "no provider found for issuer: %s", jwt->payload.iss);
		goto out;
	}


	jwk = NULL;
	if (oidc_util_create_symmetric_key(r, provider->client_secret, 0,
			NULL, TRUE, &jwk) == FALSE)
		return FALSE;

	oidc_jwks_uri_t jwks_uri = { provider->jwks_uri,
			provider->jwks_refresh_interval, provider->ssl_validate_server };
	if (oidc_proto_jwt_verify(r, cfg, jwt, &jwks_uri,
			oidc_util_merge_symmetric_key(r->pool, NULL, jwk)) == FALSE) {

		oidc_error(r, "id_token signature could not be validated, aborting");
		goto out;
	}


	if (oidc_proto_validate_jwt(r, jwt, provider->issuer, FALSE, FALSE,
			provider->idtoken_iat_slack,
			OIDC_TOKEN_BINDING_POLICY_DISABLED) == FALSE)
		goto out;


	if (oidc_proto_validate_aud_and_azp(r, cfg, provider,
			&jwt->payload) == FALSE)
		goto out;

	json_t *events = json_object_get(jwt->payload.value.json,
			OIDC_CLAIM_EVENTS);
	if (events == NULL) {
		oidc_error(r, "\"%s\" claim could not be found in logout token",
				OIDC_CLAIM_EVENTS);
		goto out;
	}

	json_t *blogout = json_object_get(events, OIDC_EVENTS_BLOGOUT_KEY);
	if (!json_is_object(blogout)) {
		oidc_error(r, "\"%s\" object could not be found in \"%s\" claim",
				OIDC_EVENTS_BLOGOUT_KEY, OIDC_CLAIM_EVENTS);
		goto out;
	}

	char *nonce = NULL;
	oidc_json_object_get_string(r->pool, jwt->payload.value.json,
			OIDC_CLAIM_NONCE, &nonce, NULL);
	if (nonce != NULL) {
		oidc_error(r,
				"rejecting logout request/token since it contains a \"%s\" claim",
				OIDC_CLAIM_NONCE);
		goto out;
	}

	char *jti = NULL;
	oidc_json_object_get_string(r->pool, jwt->payload.value.json,
			OIDC_CLAIM_JTI, &jti, NULL);
	if (jti != NULL) {
		char *replay = NULL;
		oidc_cache_get_jti(r, jti, &replay);
		if (replay != NULL) {
			oidc_error(r,
					"the \"%s\" value (%s) passed in logout token was found in the cache already; possible replay attack!?",
					OIDC_CLAIM_JTI, jti);
			goto out;
		}
	}


	apr_time_t jti_cache_duration = apr_time_from_sec(
			provider->idtoken_iat_slack * 2 + 10);


	oidc_cache_set_jti(r, jti, jti, apr_time_now() + jti_cache_duration);

	oidc_json_object_get_string(r->pool, jwt->payload.value.json,
			OIDC_CLAIM_EVENTS, &sid, NULL);


	oidc_json_object_get_string(r->pool, jwt->payload.value.json,
			OIDC_CLAIM_SID, &sid, NULL);
	if (sid == NULL)
		sid = jwt->payload.sub;

	if (sid == NULL) {
		oidc_error(r, "no \"sub\" and no \"sid\" claim found in logout token");
		goto out;
	}


	sid = oidc_make_sid_iss_unique(r, sid, provider->issuer);
	oidc_cache_get_sid(r, sid, &uuid);
	if (uuid == NULL) {
		oidc_error(r,
				"could not find session based on sid/sub provided in logout token: %s",
				sid);
		goto out;
	}


	if (cfg->session_type != OIDC_SESSION_TYPE_CLIENT_COOKIE) {
		if (oidc_session_load_cache_by_uuid(r, cfg, uuid, &session) != FALSE)
			if (oidc_session_extract(r, &session) != FALSE)
				oidc_revoke_tokens(r, cfg, &session);
	}


	oidc_cache_set_sid(r, sid, NULL, 0);
	oidc_cache_set_session(r, uuid, NULL, 0);

	rc = OK;

out:

	if (jwk != NULL) {
		oidc_jwk_destroy(jwk);
		jwk = NULL;

	}
	if (jwt != NULL) {
		oidc_jwt_destroy(jwt);
		jwt = NULL;
	}

	return rc;
}
