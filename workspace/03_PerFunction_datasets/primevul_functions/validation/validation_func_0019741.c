int oidc_handle_redirect_uri_request(request_rec *r, oidc_cfg *c,
		oidc_session_t *session) {

	if (oidc_proto_is_redirect_authorization_response(r, c)) {


		return oidc_handle_redirect_authorization_response(r, c, session);


	} else if (oidc_util_request_has_parameter(r,
			OIDC_REDIRECT_URI_REQUEST_LOGOUT)) {

		return oidc_handle_logout(r, c, session);

	} else if (oidc_proto_is_post_authorization_response(r, c)) {


		return oidc_handle_post_authorization_response(r, c, session);

	} else if (oidc_is_discovery_response(r, c)) {


		return oidc_handle_discovery_response(r, c);

	} else if (oidc_util_request_has_parameter(r,
			OIDC_REDIRECT_URI_REQUEST_JWKS)) {


		return oidc_handle_jwks(r, c);

	} else if (oidc_util_request_has_parameter(r,
			OIDC_REDIRECT_URI_REQUEST_SESSION)) {


		return oidc_handle_session_management(r, c, session);

	} else if (oidc_util_request_has_parameter(r,
			OIDC_REDIRECT_URI_REQUEST_REFRESH)) {


		return oidc_handle_refresh_token_request(r, c, session);

	} else if (oidc_util_request_has_parameter(r,
			OIDC_REDIRECT_URI_REQUEST_REQUEST_URI)) {


		return oidc_handle_request_uri(r, c);

	} else if (oidc_util_request_has_parameter(r,
			OIDC_REDIRECT_URI_REQUEST_REMOVE_AT_CACHE)) {


		return oidc_handle_remove_at_cache(r, c);

	} else if (oidc_util_request_has_parameter(r,
			OIDC_REDIRECT_URI_REQUEST_INFO)) {

		if (session->remote_user == NULL)
			return HTTP_UNAUTHORIZED;


		int rc = oidc_handle_existing_session(r, c, session);
		if (rc != OK)
			return rc;

		return oidc_handle_info_request(r, c, session);

	} else if ((r->args == NULL) || (apr_strnatcmp(r->args, "") == 0)) {


		return oidc_proto_javascript_implicit(r, c);
	}


	if (oidc_util_request_has_parameter(r, OIDC_PROTO_ERROR)) {


		return oidc_handle_redirect_authorization_response(r, c, session);
	}

	oidc_error(r,
			"The OpenID Connect callback URL received an invalid request: %s; returning HTTP_INTERNAL_SERVER_ERROR",
			r->args);


	return oidc_util_html_send_error(r, c->error_template, "Invalid Request",
			apr_psprintf(r->pool,
					"The OpenID Connect callback URL received an invalid request"),
					HTTP_INTERNAL_SERVER_ERROR);
}
