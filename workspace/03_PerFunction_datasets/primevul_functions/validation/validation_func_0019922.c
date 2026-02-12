PJ_DEF(pj_status_t) pjmedia_sdp_neg_send_local_offer( pj_pool_t *pool,
				  pjmedia_sdp_neg *neg,
				  const pjmedia_sdp_session **offer)
{

    PJ_ASSERT_RETURN(neg && offer, PJ_EINVAL);

    *offer = NULL;


    PJ_ASSERT_RETURN(neg->state == PJMEDIA_SDP_NEG_STATE_DONE ||
		     neg->state == PJMEDIA_SDP_NEG_STATE_LOCAL_OFFER,
		     PJMEDIA_SDPNEG_EINSTATE);

    if (neg->state == PJMEDIA_SDP_NEG_STATE_DONE) {

	PJ_ASSERT_RETURN(neg->active_local_sdp, PJMEDIA_SDPNEG_ENOACTIVE);


	if (neg->initial_sdp) {
	    neg->initial_sdp_tmp = neg->initial_sdp;
    	    neg->initial_sdp = pjmedia_sdp_session_clone(pool,
							 neg->initial_sdp);
	}

	neg->state = PJMEDIA_SDP_NEG_STATE_LOCAL_OFFER;
	neg->neg_local_sdp = pjmedia_sdp_session_clone(pool,
						       neg->active_local_sdp);

#if PJMEDIA_SDP_NEG_COMPARE_BEFORE_INC_VERSION
    	if (pjmedia_sdp_session_cmp(neg->neg_local_sdp,
    				    neg->initial_sdp, 0) != PJ_SUCCESS)
    	{
	    neg->neg_local_sdp->origin.version++;
    	}
#else
    	neg->neg_local_sdp->origin.version++;
#endif

	*offer = neg->neg_local_sdp;

    } else {


	*offer = neg->neg_local_sdp;
    }

    return PJ_SUCCESS;
}
