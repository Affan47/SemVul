static pj_status_t process_m_answer( pj_pool_t *pool,
				     pjmedia_sdp_media *offer,
				     pjmedia_sdp_media *answer,
				     pj_bool_t allow_asym)
{
    unsigned i;


    if (pj_strcmp(&answer->desc.media, &offer->desc.media)!=0) {

	return PJMEDIA_SDPNEG_EINVANSMEDIA;
    }


    if (pjmedia_sdp_transport_cmp(&answer->desc.transport,
				  &offer->desc.transport)
	!= PJ_SUCCESS)
    {
	return PJMEDIA_SDPNEG_EINVANSTP;
    }


    if (answer->desc.port == 0) {


	pjmedia_sdp_media_deactivate(pool, offer);


	return PJ_SUCCESS;
    }


    if (offer->desc.port == 0) {

	return PJ_SUCCESS;
    }


    update_media_direction(pool, answer, offer);


    if (allow_asym) {
	for (i=0; i<answer->desc.fmt_count; ++i) {
	    unsigned j;
	    pj_str_t *rem_fmt = &answer->desc.fmt[i];

	    for (j=0; j<offer->desc.fmt_count; ++j) {
		if (pj_strcmp(rem_fmt, &answer->desc.fmt[j])==0)
		    break;
	    }

	    if (j != offer->desc.fmt_count) {

		break;
	    }
	}

	if (i == answer->desc.fmt_count) {

	    return PJMEDIA_SDPNEG_EANSNOMEDIA;
	}

	PJ_TODO(CHECK_SDP_NEGOTIATION_WHEN_ASYMETRIC_MEDIA_IS_ALLOWED);

    } else {

	unsigned offer_fmt_prior[PJMEDIA_MAX_SDP_FMT];


	for (i=0; i<offer->desc.fmt_count;) {
	    unsigned pt;
	    pj_uint32_t j;
	    pj_str_t *fmt = &offer->desc.fmt[i];


	    pt = pj_strtoul(fmt);

	    if (pt < 96) {
		for (j=0; j<answer->desc.fmt_count; ++j) {
		    if (pj_strcmp(fmt, &answer->desc.fmt[j])==0)
			break;
		}
	    } else {


		const pjmedia_sdp_attr *a;
		pjmedia_sdp_rtpmap or_;


		a = pjmedia_sdp_media_find_attr2(offer, "rtpmap", fmt);
		if (!a) {
		    pj_assert(!"Bug! Offer should have been validated");
		    return PJ_EBUG;
		}
		pjmedia_sdp_attr_get_rtpmap(a, &or_);


		for (j=0; j<answer->desc.fmt_count; ++j) {
		    a = pjmedia_sdp_media_find_attr2(answer, "rtpmap",
						     &answer->desc.fmt[j]);
		    if (a) {
			pjmedia_sdp_rtpmap ar;
			pjmedia_sdp_attr_get_rtpmap(a, &ar);


			if (!pj_stricmp(&or_.enc_name, &ar.enc_name) &&
			    or_.clock_rate == ar.clock_rate &&
			    (pj_stricmp(&or_.param, &ar.param)==0 ||
			     (ar.param.slen==1 && *ar.param.ptr=='1')))
			{

			    if (custom_fmt_match(pool, &or_.enc_name,
						 offer, i, answer, j, 0) ==
				PJ_SUCCESS)
			    {

				break;
			    }
			}
		    }
		}
	    }

	    if (j == answer->desc.fmt_count) {


		pjmedia_sdp_attr *a;


		a = pjmedia_sdp_media_find_attr2(offer, "rtpmap", fmt);
		if (a)
		    pjmedia_sdp_media_remove_attr(offer, a);


		a = pjmedia_sdp_media_find_attr2(offer, "fmtp", fmt);
		if (a)
		    pjmedia_sdp_media_remove_attr(offer, a);


		pj_array_erase(offer->desc.fmt, sizeof(offer->desc.fmt[0]),
			       offer->desc.fmt_count, i);
		--offer->desc.fmt_count;

	    } else {
		offer_fmt_prior[i] = j;
		++i;
	    }
	}

	if (0 == offer->desc.fmt_count) {

	    return PJMEDIA_SDPNEG_EANSNOMEDIA;
	}


	for (i=0; i<offer->desc.fmt_count; ++i) {
	    unsigned j;
	    for (j=i+1; j<offer->desc.fmt_count; ++j) {
		if (offer_fmt_prior[i] > offer_fmt_prior[j]) {
		    unsigned tmp = offer_fmt_prior[i];
		    offer_fmt_prior[i] = offer_fmt_prior[j];
		    offer_fmt_prior[j] = tmp;
		    str_swap(&offer->desc.fmt[i], &offer->desc.fmt[j]);
		}
	    }
	}


	{
	    unsigned del_cnt = 0;
	    for (i=0; i<answer->desc.fmt_count;) {

		if (i >= offer->desc.fmt_count ||
		    offer_fmt_prior[i]-del_cnt != i)
		{
		    pj_str_t *fmt = &answer->desc.fmt[i];
		    pjmedia_sdp_attr *a;


		    a = pjmedia_sdp_media_find_attr2(answer, "rtpmap", fmt);
		    if (a)
			pjmedia_sdp_media_remove_attr(answer, a);


		    a = pjmedia_sdp_media_find_attr2(answer, "fmtp", fmt);
		    if (a)
			pjmedia_sdp_media_remove_attr(answer, a);


		    pj_array_erase(answer->desc.fmt,
				   sizeof(answer->desc.fmt[0]),
				   answer->desc.fmt_count, i);
		    --answer->desc.fmt_count;

		    ++del_cnt;
		} else {
		    ++i;
		}
	    }
	}
    }


    return PJ_SUCCESS;
}
