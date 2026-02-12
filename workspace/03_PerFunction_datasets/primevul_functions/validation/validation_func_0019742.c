static apr_byte_t oidc_set_app_claims(request_rec *r,
		const oidc_cfg * const cfg, oidc_session_t *session,
		const char *s_claims) {

	json_t *j_claims = NULL;


	if (s_claims != NULL) {
		if (oidc_util_decode_json_object(r, s_claims, &j_claims) == FALSE)
			return FALSE;
	}


	if (j_claims != NULL) {
		oidc_util_set_app_infos(r, j_claims, oidc_cfg_claim_prefix(r),
				cfg->claim_delimiter, oidc_cfg_dir_pass_info_in_headers(r),
				oidc_cfg_dir_pass_info_in_envvars(r));


		json_decref(j_claims);
	}

	return TRUE;
}
