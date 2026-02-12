PJ_DEF(pj_status_t) pjmedia_sdp_attr_get_rtcp(const pjmedia_sdp_attr *attr,
					      pjmedia_sdp_rtcp_attr *rtcp)
{
    pj_scanner scanner;
    pj_str_t token;
    pj_status_t status = -1;
    PJ_USE_EXCEPTION;

    PJ_ASSERT_RETURN(pj_strcmp2(&attr->name, "rtcp")==0, PJ_EINVALIDOP);

    if (attr->value.slen == 0)
        return PJMEDIA_SDP_EINATTR;

    init_sdp_parser();


    pj_scan_init(&scanner, (char*)attr->value.ptr, attr->value.slen,
		 PJ_SCAN_AUTOSKIP_WS, &on_scanner_error);


    rtcp->net_type.slen = rtcp->addr_type.slen = rtcp->addr.slen = 0;


    PJ_TRY {


	pj_scan_get(&scanner, &cs_token, &token);
	rtcp->port = pj_strtoul(&token);


	if (!pj_scan_is_eof(&scanner)) {


	    pj_scan_get(&scanner, &cs_token, &rtcp->net_type);


	    pj_scan_get(&scanner, &cs_token, &rtcp->addr_type);


	    pj_scan_get_until_chr(&scanner, "/ \t\r\n", &rtcp->addr);

	}

	status = PJ_SUCCESS;

    }
    PJ_CATCH_ANY {
	status = PJMEDIA_SDP_EINRTCP;
    }
    PJ_END;

    pj_scan_fini(&scanner);
    return status;
}
