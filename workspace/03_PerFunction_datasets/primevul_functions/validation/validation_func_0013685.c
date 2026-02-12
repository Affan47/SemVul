static int oidc_handle_unauthenticated_user(request_rec *r, oidc_cfg *c) {


	switch (oidc_dir_cfg_unauth_action(r)) {
	case OIDC_UNAUTH_RETURN410:
		return HTTP_GONE;
	case OIDC_UNAUTH_RETURN407:
		return HTTP_PROXY_AUTHENTICATION_REQUIRED;
	case OIDC_UNAUTH_RETURN401:
		return HTTP_UNAUTHORIZED;
	case OIDC_UNAUTH_PASS:
		r->user = "";


		oidc_scrub_headers(r);

		return OK;

	case OIDC_UNAUTH_AUTHENTICATE:


		if ((oidc_dir_cfg_unauth_expr_is_set(r) == FALSE)
				&& (oidc_is_xml_http_request(r) == TRUE))
			return HTTP_UNAUTHORIZED;
	}


	return oidc_authenticate_user(r, c, NULL, oidc_get_current_url(r), NULL,
			NULL, NULL, oidc_dir_cfg_path_auth_request_params(r),
			oidc_dir_cfg_path_scope(r));
}
