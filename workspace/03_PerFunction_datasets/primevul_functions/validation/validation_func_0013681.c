static const char* oidc_retrieve_claims_from_userinfo_endpoint(request_rec *r,
		oidc_cfg *c, oidc_provider_t *provider, const char *access_token,
		oidc_session_t *session, char *id_token_sub, char **userinfo_jwt) {

	oidc_debug(r, "enter");

	char *result = NULL;
	char *refreshed_access_token = NULL;


	if (provider->userinfo_endpoint_url == NULL) {
		oidc_debug(r,
				"not retrieving userinfo claims because userinfo_endpoint is not set");
		return NULL;
	}


	if (access_token == NULL) {
		oidc_debug(r,
				"not retrieving userinfo claims because access_token is not provided");
		return NULL;
	}

	if ((id_token_sub == NULL) && (session != NULL)) {


		json_t *id_token_claims = oidc_session_get_idtoken_claims_json(r,
				session);
		if (id_token_claims == NULL) {
			oidc_error(r, "no id_token_claims found in session");
			return NULL;
		}

		oidc_jose_get_string(r->pool, id_token_claims, OIDC_CLAIM_SUB, FALSE,
				&id_token_sub, NULL);
	}


	if (oidc_proto_resolve_userinfo(r, c, provider, id_token_sub, access_token,
			&result, userinfo_jwt) == FALSE) {


		if (session != NULL) {


			if (oidc_refresh_access_token(r, c, session, provider,
					&refreshed_access_token) == TRUE) {


				if (oidc_proto_resolve_userinfo(r, c, provider, id_token_sub,
						refreshed_access_token, &result, userinfo_jwt)
						== FALSE) {

					oidc_error(r,
							"resolving user info claims with the refreshed access token failed, nothing will be stored in the session");
					result = NULL;

				}

			} else {

				oidc_warn(r,
						"refreshing access token failed, claims will not be retrieved/refreshed from the userinfo endpoint");
				result = NULL;

			}

		} else {

			oidc_error(r,
					"resolving user info claims with the existing/provided access token failed, nothing will be stored in the session");
			result = NULL;

		}
	}

	return result;
}
