static apr_byte_t oidc_restore_proto_state(request_rec *r, oidc_cfg *c,
		const char *state, oidc_proto_state_t **proto_state) {

	oidc_debug(r, "enter");

	const char *cookieName = oidc_get_state_cookie_name(r, state);


	oidc_clean_expired_state_cookies(r, c, cookieName, FALSE);


	char *cookieValue = oidc_util_get_cookie(r, cookieName);
	if (cookieValue == NULL) {
		oidc_error(r, "no \"%s\" state cookie found", cookieName);
		return oidc_unsolicited_proto_state(r, c, state, proto_state);
	}


	oidc_util_set_cookie(r, cookieName, "", 0, NULL);

	*proto_state = oidc_proto_state_from_cookie(r, c, cookieValue);
	if (*proto_state == NULL)
		return FALSE;

	const char *nonce = oidc_proto_state_get_nonce(*proto_state);


	char *calc = oidc_get_browser_state_hash(r, nonce);

	if (apr_strnatcmp(calc, state) != 0) {
		oidc_error(r,
				"calculated state from cookie does not match state parameter passed back in URL: \"%s\" != \"%s\"",
				state, calc);
		oidc_proto_state_destroy(*proto_state);
		return FALSE;
	}

	apr_time_t ts = oidc_proto_state_get_timestamp(*proto_state);


	if (apr_time_now() > ts + apr_time_from_sec(c->state_timeout)) {
		oidc_error(r, "state has expired");


		oidc_util_html_send_error(r, c->error_template,
				"Invalid Authentication Response",
				apr_psprintf(r->pool,
						"This is due to a timeout; please restart your authentication session by re-entering the URL/bookmark you originally wanted to access: %s",
						oidc_proto_state_get_original_url(*proto_state)),
						OK);
		oidc_proto_state_destroy(*proto_state);
		return FALSE;
	}


	oidc_proto_state_set_state(*proto_state, state);


	oidc_debug(r, "restored state: %s",
			oidc_proto_state_to_string(r, *proto_state));


	return TRUE;
}
