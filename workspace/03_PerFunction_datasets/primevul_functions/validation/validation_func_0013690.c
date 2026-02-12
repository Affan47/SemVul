static int oidc_check_userid_openidc(request_rec *r, oidc_cfg *c) {

	if (oidc_get_redirect_uri(r, c) == NULL) {
		oidc_error(r,
				"configuration error: the authentication type is set to \"" OIDC_AUTH_TYPE_OPENID_CONNECT "\" but " OIDCRedirectURI " has not been set");
		return HTTP_INTERNAL_SERVER_ERROR;
	}


	if (!ap_is_initial_req(r)) {


		if (r->main != NULL)
			r->user = r->main->user;
		else if (r->prev != NULL)
			r->user = r->prev->user;

		if (r->user != NULL) {


			oidc_debug(r,
					"recycling user '%s' from initial request for sub-request",
					r->user);


			const char *s_id_token = oidc_request_state_get(r,
					OIDC_REQUEST_STATE_KEY_IDTOKEN);
			if (s_id_token == NULL) {

				oidc_session_t *session = NULL;
				oidc_session_load(r, &session);

				oidc_copy_tokens_to_request_state(r, session, NULL, NULL);


				oidc_session_free(r, session);
			}


			oidc_strip_cookies(r);

			return OK;
		}


	}

	int rc = OK;
	apr_byte_t needs_save = FALSE;


	oidc_session_t *session = NULL;
	oidc_session_load(r, &session);


	if (oidc_util_request_matches_url(r, oidc_get_redirect_uri(r, c))) {


		rc = oidc_handle_redirect_uri_request(r, c, session);


		oidc_session_free(r, session);

		return rc;


	} else if (session->remote_user != NULL) {


		rc = oidc_handle_existing_session(r, c, session, &needs_save);
		if (rc == OK) {


			if (needs_save) {
				if (oidc_session_save(r, session, FALSE) == FALSE) {
					oidc_warn(r, "error saving session");
					rc = HTTP_INTERNAL_SERVER_ERROR;
				}
			}
		}


		oidc_session_free(r, session);


		oidc_strip_cookies(r);

		return rc;
	}


	oidc_session_free(r, session);


	return oidc_handle_unauthenticated_user(r, c);
}
