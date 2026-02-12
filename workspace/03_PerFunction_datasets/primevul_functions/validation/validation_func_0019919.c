PJ_DEF(pj_status_t) pjmedia_sdp_neg_set_local_answer( pj_pool_t *pool,
				  pjmedia_sdp_neg *neg,
				  const pjmedia_sdp_session *local)
{

    PJ_ASSERT_RETURN(pool && neg && local, PJ_EINVAL);


    PJ_ASSERT_RETURN(neg->state == PJMEDIA_SDP_NEG_STATE_REMOTE_OFFER ||
    		     neg->state == PJMEDIA_SDP_NEG_STATE_WAIT_NEGO,
		     PJMEDIA_SDPNEG_EINSTATE);


    neg->state = PJMEDIA_SDP_NEG_STATE_WAIT_NEGO;
    if (local) {
	neg->neg_local_sdp = pjmedia_sdp_session_clone(pool, local);
	if (neg->initial_sdp) {

	    neg->initial_sdp_tmp = neg->initial_sdp;
	    neg->initial_sdp = pjmedia_sdp_session_clone(pool,
							 neg->initial_sdp);


	    neg->neg_local_sdp->origin.id = neg->initial_sdp->origin.id;
	} else {
	    neg->initial_sdp = pjmedia_sdp_session_clone(pool, local);
	}
    } else {
	PJ_ASSERT_RETURN(neg->initial_sdp, PJMEDIA_SDPNEG_ENOINITIAL);
	neg->initial_sdp_tmp = neg->initial_sdp;
	neg->initial_sdp = pjmedia_sdp_session_clone(pool, neg->initial_sdp);
	neg->neg_local_sdp = pjmedia_sdp_session_clone(pool, neg->initial_sdp);
    }

    return PJ_SUCCESS;
}
