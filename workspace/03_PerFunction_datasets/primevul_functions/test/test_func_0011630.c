PJ_DEF(pj_status_t) pjmedia_sdp_transport_cmp( const pj_str_t *t1,
					       const pj_str_t *t2)
{
    pj_uint32_t t1_proto, t2_proto;


    if (pj_stricmp(t1, t2) == 0)
	return PJ_SUCCESS;


    t1_proto = pjmedia_sdp_transport_get_proto(t1);
    t2_proto = pjmedia_sdp_transport_get_proto(t2);
    if (PJMEDIA_TP_PROTO_HAS_FLAG(t1_proto, PJMEDIA_TP_PROTO_RTP_AVP) &&
	PJMEDIA_TP_PROTO_HAS_FLAG(t2_proto, PJMEDIA_TP_PROTO_RTP_AVP))
    {
	return PJ_SUCCESS;
    }


    return PJMEDIA_SDP_ETPORTNOTEQUAL;
}
