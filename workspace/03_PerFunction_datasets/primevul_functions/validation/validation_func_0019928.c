static void apply_answer_symmetric_pt(pj_pool_t *pool,
				      pjmedia_sdp_media *answer,
				      unsigned pt_cnt,
				      const pj_str_t pt_offer[],
				      const pj_str_t pt_answer[])
{
    pjmedia_sdp_attr *a_tmp[PJMEDIA_MAX_SDP_ATTR];
    unsigned i, a_tmp_cnt = 0;


    for (i = 0; i < pt_cnt; ++i) {
	pjmedia_sdp_attr *a;


	if (pj_strcmp(&pt_answer[i], &pt_offer[i]) == 0)
	    continue;


	pj_strdup(pool, &answer->desc.fmt[i], &pt_offer[i]);


	a = pjmedia_sdp_media_find_attr2(answer, "rtpmap", &pt_answer[i]);
	if (a) {
	    rewrite_pt(pool, &a->value, &pt_answer[i], &pt_offer[i]);


	    pjmedia_sdp_media_remove_attr(answer, a);
	    a_tmp[a_tmp_cnt++] = a;
	}


	a = pjmedia_sdp_media_find_attr2(answer, "fmtp", &pt_answer[i]);
	if (a) {
	    rewrite_pt(pool, &a->value, &pt_answer[i], &pt_offer[i]);


	    pjmedia_sdp_media_remove_attr(answer, a);
	    a_tmp[a_tmp_cnt++] = a;
	}
    }


    for (i = 0; i < a_tmp_cnt; ++i)
	pjmedia_sdp_media_add_attr(answer, a_tmp[i]);
}
