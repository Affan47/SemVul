init_ctx_nego(OM_uint32 *minor_status, spnego_gss_ctx_id_t sc,
	      OM_uint32 acc_negState, gss_OID supportedMech,
	      gss_buffer_t *responseToken, gss_buffer_t *mechListMIC,
	      OM_uint32 *negState, send_token_flag *tokflag)
{
	OM_uint32 ret;

	*negState = REJECT;
	*tokflag = ERROR_TOKEN_SEND;
	ret = GSS_S_DEFECTIVE_TOKEN;


	if (supportedMech == GSS_C_NO_OID) {
		*minor_status = ERR_SPNEGO_NO_MECH_FROM_ACCEPTOR;
		map_errcode(minor_status);
		return GSS_S_DEFECTIVE_TOKEN;
	}
	if (acc_negState == ACCEPT_DEFECTIVE_TOKEN) {
		*minor_status = ERR_SPNEGO_NEGOTIATION_FAILED;
		map_errcode(minor_status);
		return GSS_S_DEFECTIVE_TOKEN;
	}


	if (!(is_kerb_mech(supportedMech) &&
	      is_kerb_mech(sc->internal_mech)) &&
	    !g_OID_equal(supportedMech, sc->internal_mech)) {
		ret = init_ctx_reselect(minor_status, sc,
					acc_negState, supportedMech,
					responseToken, mechListMIC,
					negState, tokflag);

	} else if (*responseToken == GSS_C_NO_BUFFER) {
		if (sc->mech_complete) {


			*negState = ACCEPT_COMPLETE;
			*tokflag = NO_TOKEN_SEND;
			ret = GSS_S_COMPLETE;
		} else {


			*minor_status = ERR_SPNEGO_NO_TOKEN_FROM_ACCEPTOR;
			map_errcode(minor_status);
			ret = GSS_S_DEFECTIVE_TOKEN;
		}
	} else if ((*responseToken)->length == 0 && sc->mech_complete) {


		*negState = ACCEPT_COMPLETE;
		*tokflag = NO_TOKEN_SEND;
		ret = GSS_S_COMPLETE;
	} else if (sc->mech_complete) {

		ret = GSS_S_DEFECTIVE_TOKEN;
	} else {
		*negState = ACCEPT_INCOMPLETE;
		*tokflag = CONT_TOKEN_SEND;
		ret = GSS_S_CONTINUE_NEEDED;
	}
	sc->nego_done = 1;
	return ret;
}
