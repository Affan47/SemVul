PJ_DEF(pj_uint32_t) pjmedia_sdp_transport_get_proto(const pj_str_t *tp)
{
    pj_str_t token, rest = {0};
    pj_ssize_t idx;

    PJ_ASSERT_RETURN(tp, PJMEDIA_TP_PROTO_NONE);

    idx = pj_strtok2(tp, "/", &token, 0);
    if (idx != tp->slen)
	pj_strset(&rest, tp->ptr + token.slen + 1, tp->slen - token.slen - 1);

    if (pj_stricmp2(&token, "RTP") == 0) {


	if (pj_stricmp2(&rest, "AVP") == 0)
	    return PJMEDIA_TP_PROTO_RTP_AVP;


	if (pj_stricmp2(&rest, "SAVP") == 0)
	    return PJMEDIA_TP_PROTO_RTP_SAVP;


	if (pj_stricmp2(&rest, "AVPF") == 0)
	    return PJMEDIA_TP_PROTO_RTP_AVPF;


	if (pj_stricmp2(&rest, "SAVPF") == 0)
	    return PJMEDIA_TP_PROTO_RTP_SAVPF;

    } else if (pj_stricmp2(&token, "UDP") == 0) {


	if (rest.slen == 0)
	    return PJMEDIA_TP_PROTO_UDP;


	if (pj_stricmp2(&rest, "TLS/RTP/SAVP") == 0)
	    return PJMEDIA_TP_PROTO_DTLS_SRTP;


	if (pj_stricmp2(&rest, "TLS/RTP/SAVPF") == 0)
	    return PJMEDIA_TP_PROTO_DTLS_SRTPF;
    }


    return PJMEDIA_TP_PROTO_UNKNOWN;
}
