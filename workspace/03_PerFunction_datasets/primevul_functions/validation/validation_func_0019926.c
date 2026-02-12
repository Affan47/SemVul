PJ_DEF(pj_status_t) pjmedia_sdp_neg_set_remote_offer( pj_pool_t *pool,
				  pjmedia_sdp_neg *neg,
				  const pjmedia_sdp_session *remote)
{

    PJ_ASSERT_RETURN(pool && neg && remote, PJ_EINVAL);


    PJ_ASSERT_RETURN(neg->state == PJMEDIA_SDP_NEG_STATE_DONE,
		     PJMEDIA_SDPNEG_EINSTATE);


    neg->state = PJMEDIA_SDP_NEG_STATE_REMOTE_OFFER;
    neg->neg_remote_sdp = pjmedia_sdp_session_clone(pool, remote);

    return PJ_SUCCESS;
}
