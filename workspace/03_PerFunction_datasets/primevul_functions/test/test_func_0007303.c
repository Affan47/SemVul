PJ_DEF(pj_status_t) pjmedia_rtcp_fb_build_sli(
					pjmedia_rtcp_session *session,
					void *buf,
					pj_size_t *length,
					unsigned sli_cnt,
					const pjmedia_rtcp_fb_sli sli[])
{
    pjmedia_rtcp_fb_common *hdr;
    pj_uint8_t *p;
    unsigned len, i;

    PJ_ASSERT_RETURN(session && buf && length && sli_cnt && sli, PJ_EINVAL);

    len = (3 + sli_cnt) * 4;
    if (len > *length)
	return PJ_ETOOSMALL;


    hdr = (pjmedia_rtcp_fb_common*)buf;
    pj_memcpy(hdr, &session->rtcp_fb_com, sizeof(*hdr));
    hdr->rtcp_common.pt = RTCP_PSFB;
    hdr->rtcp_common.count = 2;
    hdr->rtcp_common.length = pj_htons((pj_uint16_t)(len/4 - 1));


    p = (pj_uint8_t*)hdr + sizeof(*hdr);
    for (i = 0; i < sli_cnt; ++i) {

	*p++  = (pj_uint8_t)((sli[i].first >> 5) & 0xFF);
	*p    = (pj_uint8_t)((sli[i].first & 31) << 3);

	*p++ |= (pj_uint8_t)((sli[i].number >> 10) & 7);
	*p++  = (pj_uint8_t)((sli[i].number >> 2) & 0xFF);
	*p    = (pj_uint8_t)((sli[i].number & 3) << 6);

	*p++ |= (sli[i].pict_id & 63);
    }


    *length = len;

    return PJ_SUCCESS;
}
