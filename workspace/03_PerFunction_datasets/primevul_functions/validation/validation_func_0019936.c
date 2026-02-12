static pj_status_t process_answer(pj_pool_t *pool,
				  pjmedia_sdp_session *local_offer,
				  pjmedia_sdp_session *answer,
				  pj_bool_t allow_asym,
				  pjmedia_sdp_session **p_active)
{
    unsigned omi = 0;
    unsigned ami = 0;
    pj_bool_t has_active = PJ_FALSE;
    pjmedia_sdp_session *offer;
    pj_status_t status;


    PJ_ASSERT_RETURN(pool && local_offer && answer && p_active, PJ_EINVAL);


    offer = pjmedia_sdp_session_clone(pool, local_offer);


    for (; omi<offer->media_count; ++omi) {
	if (ami == answer->media_count) {

	    pjmedia_sdp_media *am;


	    am = sdp_media_clone_deactivate(pool, offer->media[omi],
	                                    offer->media[omi], offer);
	    answer->media[answer->media_count++] = am;
	    ++ami;


	    pjmedia_sdp_media_deactivate(pool, offer->media[omi]);


	    continue;
	}

	status = process_m_answer(pool, offer->media[omi], answer->media[ami],
				  allow_asym);


	if (status == PJMEDIA_SDPNEG_EINVANSMEDIA) {
	    pjmedia_sdp_media_deactivate(pool, offer->media[omi]);
	    continue;
	}

	else if (status == PJMEDIA_SDPNEG_EANSNOMEDIA) {
	    pjmedia_sdp_media_deactivate(pool, offer->media[omi]);
	    pjmedia_sdp_media_deactivate(pool, answer->media[ami]);
	}

	else if (status != PJ_SUCCESS) {
	    return status;
	}

	if (offer->media[omi]->desc.port != 0)
	    has_active = PJ_TRUE;

	++ami;
    }

    *p_active = offer;

    return has_active ? PJ_SUCCESS : PJMEDIA_SDPNEG_ENOMEDIA;
}
