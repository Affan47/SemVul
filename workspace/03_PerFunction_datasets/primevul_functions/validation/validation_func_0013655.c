static apr_byte_t oidc_is_discovery_response(request_rec *r, oidc_cfg *cfg) {


	return oidc_util_request_has_parameter(r, OIDC_DISC_OP_PARAM)
			|| oidc_util_request_has_parameter(r, OIDC_DISC_USER_PARAM);
}
