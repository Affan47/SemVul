PJ_DEF(pj_status_t) pjmedia_sdp_neg_cancel_offer(pjmedia_sdp_neg *neg)
{
    PJ_ASSERT_RETURN(neg, PJ_EINVAL);


    PJ_ASSERT_RETURN(neg->state == PJMEDIA_SDP_NEG_STATE_LOCAL_OFFER ||
		     neg->state == PJMEDIA_SDP_NEG_STATE_REMOTE_OFFER,
		     PJMEDIA_SDPNEG_EINSTATE);

    if (neg->state == PJMEDIA_SDP_NEG_STATE_LOCAL_OFFER &&
	neg->active_local_sdp)
    {


	neg->active_local_sdp->origin.version++;
    }


    if (neg->state == PJMEDIA_SDP_NEG_STATE_LOCAL_OFFER)
	neg->initial_sdp = neg->initial_sdp_tmp;


    neg->initial_sdp_tmp = NULL;
    neg->neg_local_sdp = neg->neg_remote_sdp = NULL;
    neg->has_remote_answer = PJ_FALSE;


    neg->state = PJMEDIA_SDP_NEG_STATE_DONE;

    return PJ_SUCCESS;
}
