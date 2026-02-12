static pj_status_t create_answer( pj_pool_t *pool,
				  pj_bool_t prefer_remote_codec_order,
                                  pj_bool_t answer_with_multiple_codecs,
				  const pjmedia_sdp_session *initial,
				  const pjmedia_sdp_session *offer,
				  pjmedia_sdp_session **p_answer)
{
    pj_status_t status = PJMEDIA_SDPNEG_ENOMEDIA;
    pj_bool_t has_active = PJ_FALSE;
    pjmedia_sdp_session *answer;
    char media_used[PJMEDIA_MAX_SDP_MEDIA];
    unsigned i;


    PJ_ASSERT_RETURN((status=pjmedia_sdp_validate(offer))==PJ_SUCCESS, status);


    answer = pjmedia_sdp_session_clone(pool, initial);
    PJ_ASSERT_RETURN(answer != NULL, PJ_ENOMEM);

    answer->media_count = 0;

    pj_bzero(media_used, sizeof(media_used));


    for (i=0; i<offer->media_count; ++i) {
	const pjmedia_sdp_media *om;
	const pjmedia_sdp_media *im;
	pjmedia_sdp_media *am = NULL;
	unsigned j;

	om = offer->media[i];


	for (im=NULL, j=0; j<initial->media_count; ++j) {
	    im = initial->media[j];
	    if (pj_strcmp(&om->desc.media, &im->desc.media)==0 &&
		pj_strcmp(&om->desc.transport, &im->desc.transport)==0 &&
		media_used[j] == 0)
	    {
                pj_status_t status2;


		status2 = match_offer(pool, prefer_remote_codec_order,
                                      answer_with_multiple_codecs,
				      om, im, initial, &am);
		if (status2 == PJ_SUCCESS) {

		    media_used[j] = 1;
		    break;
                } else {
                    status = status2;
                }
	    }
	}

	if (j==initial->media_count) {


	    am = sdp_media_clone_deactivate(pool, om, om, answer);
	} else {

	    pj_assert(am != NULL);
	}


	answer->media[answer->media_count++] = am;


	if (am->desc.port != 0)
	    has_active = PJ_TRUE;
    }

    *p_answer = answer;

    return has_active ? PJ_SUCCESS : status;
}
