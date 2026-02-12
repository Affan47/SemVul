static int oidc_handle_logout_request(request_rec *r, oidc_cfg *c,
		oidc_session_t *session, const char *url) {

	oidc_debug(r, "enter (url=%s)", url);


	if (session->remote_user != NULL)
		oidc_revoke_tokens(r, c, session);


	oidc_session_kill(r, session);


	if (oidc_is_front_channel_logout(url)) {


		oidc_util_hdr_err_out_add(r, OIDC_HTTP_HDR_CACHE_CONTROL,
				"no-cache, no-store");
		oidc_util_hdr_err_out_add(r, OIDC_HTTP_HDR_PRAGMA, "no-cache");
		oidc_util_hdr_err_out_add(r, OIDC_HTTP_HDR_P3P, "CAO PSA OUR");
		oidc_util_hdr_err_out_add(r, OIDC_HTTP_HDR_EXPIRES, "0");
		oidc_util_hdr_err_out_add(r, OIDC_HTTP_HDR_X_FRAME_OPTIONS, "DENY");


		const char *accept = oidc_util_hdr_in_accept_get(r);
		if ((apr_strnatcmp(url, OIDC_IMG_STYLE_LOGOUT_PARAM_VALUE) == 0)
				|| ((accept) && strstr(accept, OIDC_CONTENT_TYPE_IMAGE_PNG))) {
			return oidc_util_http_send(r, (const char*) &oidc_transparent_pixel,
					sizeof(oidc_transparent_pixel), OIDC_CONTENT_TYPE_IMAGE_PNG,
					OK);
		}


		return oidc_util_html_send(r, "Logged Out", NULL, NULL,
				"<p>Logged Out</p>", OK);
	}


	if (url == NULL)
		return oidc_util_html_send(r, "Logged Out", NULL, NULL,
				"<p>Logged Out</p>", OK);


	oidc_util_hdr_out_location_set(r, url);

	return HTTP_MOVED_TEMPORARILY;
}
