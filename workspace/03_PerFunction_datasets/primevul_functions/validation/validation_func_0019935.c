static pj_status_t match_offer(pj_pool_t *pool,
			       pj_bool_t prefer_remote_codec_order,
                               pj_bool_t answer_with_multiple_codecs,
			       const pjmedia_sdp_media *offer,
			       const pjmedia_sdp_media *preanswer,
			       const pjmedia_sdp_session *preanswer_sdp,
			       pjmedia_sdp_media **p_answer)
{
    unsigned i;
    pj_bool_t master_has_codec = 0,
	      master_has_other = 0,
	      found_matching_codec = 0,
	      found_matching_telephone_event = 0,
	      found_matching_other = 0;
    unsigned pt_answer_count = 0;
    pj_str_t pt_answer[PJMEDIA_MAX_SDP_FMT];
    pj_str_t pt_offer[PJMEDIA_MAX_SDP_FMT];
    pjmedia_sdp_media *answer;
    const pjmedia_sdp_media *master, *slave;
    unsigned nclockrate = 0, clockrate[PJMEDIA_MAX_SDP_FMT];
    unsigned ntel_clockrate = 0, tel_clockrate[PJMEDIA_MAX_SDP_FMT];


    if (offer->desc.port == 0) {
	answer = sdp_media_clone_deactivate(pool, offer, preanswer,
					    preanswer_sdp);
	*p_answer = answer;
	return PJ_SUCCESS;
    }


    if (preanswer->desc.port == 0) {
	answer = pjmedia_sdp_media_clone(pool, preanswer);
	*p_answer = answer;
	return PJ_SUCCESS;
    }


    if (prefer_remote_codec_order) {
	master = offer;
	slave  = preanswer;
    } else {
	master = preanswer;
	slave  = offer;
    }


    for (i=0; i<master->desc.fmt_count; ++i) {
	unsigned j;

	if (pj_isdigit(*master->desc.fmt[i].ptr)) {


	    unsigned pt;

	    pt = pj_strtoul(&master->desc.fmt[i]);

	    if (pt < 96) {


		master_has_codec = 1;


		if (!answer_with_multiple_codecs && found_matching_codec)
		    continue;


		for (j=0; j<slave->desc.fmt_count; ++j) {
		    unsigned p;
		    p = pj_strtoul(&slave->desc.fmt[j]);
		    if (p == pt && pj_isdigit(*slave->desc.fmt[j].ptr)) {
			unsigned k;

			found_matching_codec = 1;
			pt_offer[pt_answer_count] = slave->desc.fmt[j];
			pt_answer[pt_answer_count++] = slave->desc.fmt[j];


			for (k=0; k<nclockrate; ++k)
			    if (clockrate[k] == 8000)
				break;
			if (k == nclockrate)
			    clockrate[nclockrate++] = 8000;
			break;
		    }
		}

	    } else {


		const pjmedia_sdp_attr *a;
		pjmedia_sdp_rtpmap or_;
		pj_bool_t is_codec = 0;


		a = pjmedia_sdp_media_find_attr2(master, "rtpmap",
						 &master->desc.fmt[i]);
		if (!a) {
		    pj_assert(!"Bug! Offer should have been validated");
		    return PJMEDIA_SDP_EMISSINGRTPMAP;
		}
		pjmedia_sdp_attr_get_rtpmap(a, &or_);

		if (pj_stricmp2(&or_.enc_name, "telephone-event")) {
		    master_has_codec = 1;
		    if (!answer_with_multiple_codecs && found_matching_codec)
			continue;
		    is_codec = 1;
		}


		for (j=0; j<slave->desc.fmt_count; ++j) {
		    a = pjmedia_sdp_media_find_attr2(slave, "rtpmap",
						     &slave->desc.fmt[j]);
		    if (a) {
			pjmedia_sdp_rtpmap lr;
			pjmedia_sdp_attr_get_rtpmap(a, &lr);


			if (!pj_stricmp(&or_.enc_name, &lr.enc_name) &&
			    or_.clock_rate == lr.clock_rate &&
			    (pj_stricmp(&or_.param, &lr.param)==0 ||
			     (lr.param.slen==0 && or_.param.slen==1 &&
						 *or_.param.ptr=='1') ||
			     (or_.param.slen==0 && lr.param.slen==1 &&
						  *lr.param.ptr=='1')))
			{

			    if (is_codec) {
				pjmedia_sdp_media *o_med, *a_med;
				unsigned o_fmt_idx, a_fmt_idx;
				unsigned k;

				o_med = (pjmedia_sdp_media*)offer;
				a_med = (pjmedia_sdp_media*)preanswer;
				o_fmt_idx = prefer_remote_codec_order? i:j;
				a_fmt_idx = prefer_remote_codec_order? j:i;


				if (custom_fmt_match(pool, &or_.enc_name,
						     o_med, o_fmt_idx,
						     a_med, a_fmt_idx,
						     ALLOW_MODIFY_ANSWER) !=
				    PJ_SUCCESS)
				{
				    continue;
				}
				found_matching_codec = 1;


				for (k=0; k<nclockrate; ++k)
				    if (clockrate[k] == or_.clock_rate)
					break;
				if (k == nclockrate)
				    clockrate[nclockrate++] = or_.clock_rate;
			    } else {
			    	unsigned k;


				for (k=0; k<ntel_clockrate; ++k)
				    if (tel_clockrate[k] == or_.clock_rate)
					break;
				if (k < ntel_clockrate)
				    continue;

				tel_clockrate[ntel_clockrate++] = or_.clock_rate;
				found_matching_telephone_event = 1;
			    }

			    pt_offer[pt_answer_count] =
						prefer_remote_codec_order?
						offer->desc.fmt[i]:
						offer->desc.fmt[j];
			    pt_answer[pt_answer_count++] =
						prefer_remote_codec_order?
						preanswer->desc.fmt[j]:
						preanswer->desc.fmt[i];
			    break;
			}
		    }
		}
	    }

	} else {


	    master_has_other = 1;
	    if (found_matching_other)
		continue;

	    for (j=0; j<slave->desc.fmt_count; ++j) {
		if (!pj_strcmp(&master->desc.fmt[i], &slave->desc.fmt[j])) {

		    found_matching_other = 1;
		    pt_offer[pt_answer_count] = prefer_remote_codec_order?
						offer->desc.fmt[i]:
						offer->desc.fmt[j];
		    pt_answer[pt_answer_count++] = prefer_remote_codec_order?
						   preanswer->desc.fmt[j]:
						   preanswer->desc.fmt[i];
		    break;
		}
	    }
	}
    }


    if (master_has_codec && !found_matching_codec) {
	return PJMEDIA_SDPNEG_NOANSCODEC;
    }


    if (master_has_other && !found_matching_other) {
	return PJMEDIA_SDPNEG_NOANSUNKNOWN;
    }


    if (found_matching_telephone_event) {
	pj_str_t first_televent_offer = {0};
	pj_str_t first_televent_answer = {0};
	unsigned matched_cnt = 0;

	for (i=0; i<pt_answer_count; ) {
	    const pjmedia_sdp_attr *a;
	    pjmedia_sdp_rtpmap r;
	    unsigned j;


	    if (!pj_isdigit(*pt_answer[i].ptr) || pj_strtol(&pt_answer[i])<96)
	    {
		++i;
		continue;
	    }


	    a = pjmedia_sdp_media_find_attr2(preanswer, "rtpmap",
					     &pt_answer[i]);
	    pj_assert(a);
	    pjmedia_sdp_attr_get_rtpmap(a, &r);


	    if (pj_stricmp2(&r.enc_name, "telephone-event")) {
		++i;
		continue;
	    }

	    if (first_televent_offer.slen == 0) {
		first_televent_offer = pt_offer[i];
		first_televent_answer = pt_answer[i];
	    }

	    for (j=0; j<nclockrate; ++j) {
		if (r.clock_rate==clockrate[j])
		    break;
	    }


	    if (j==nclockrate) {
		pj_array_erase(pt_answer, sizeof(pt_answer[0]),
			       pt_answer_count, i);
		pj_array_erase(pt_offer, sizeof(pt_offer[0]),
			       pt_answer_count, i);
		pt_answer_count--;
	    } else {
		++matched_cnt;
		++i;
	    }
	}


	if (!matched_cnt) {
	    pt_offer[pt_answer_count] = first_televent_offer;
	    pt_answer[pt_answer_count++] = first_televent_answer;
	}
    }


    answer = pjmedia_sdp_media_clone(pool, preanswer);
    for (i=0; i<pt_answer_count; ++i) {
	unsigned j;
	for (j=i; j<answer->desc.fmt_count; ++j) {
	    if (!pj_strcmp(&answer->desc.fmt[j], &pt_answer[i]))
		break;
	}
	pj_assert(j != answer->desc.fmt_count);
	str_swap(&answer->desc.fmt[i], &answer->desc.fmt[j]);
    }


    for (i=pt_answer_count; i<answer->desc.fmt_count; ++i) {
	pjmedia_sdp_attr *a;


	a = pjmedia_sdp_media_find_attr2(answer, "rtpmap",
					 &answer->desc.fmt[i]);
	if (a) {
	    pjmedia_sdp_media_remove_attr(answer, a);
	}


	a = pjmedia_sdp_media_find_attr2(answer, "fmtp",
					 &answer->desc.fmt[i]);
	if (a) {
	    pjmedia_sdp_media_remove_attr(answer, a);
	}
    }
    answer->desc.fmt_count = pt_answer_count;

#if PJMEDIA_SDP_NEG_ANSWER_SYMMETRIC_PT
    apply_answer_symmetric_pt(pool, answer, pt_answer_count,
			      pt_offer, pt_answer);
#endif


    update_media_direction(pool, offer, answer);

    *p_answer = answer;
    return PJ_SUCCESS;
}
