PJ_DEF(pj_status_t) pjmedia_sdp_attr_get_rtpmap( const pjmedia_sdp_attr *attr,
						 pjmedia_sdp_rtpmap *rtpmap)
{
    pj_scanner scanner;
    pj_str_t token;
    pj_status_t status = -1;
    char term = 0;
    PJ_USE_EXCEPTION;

    PJ_ASSERT_RETURN(pj_strcmp2(&attr->name, "rtpmap")==0, PJ_EINVALIDOP);

    if (attr->value.slen == 0)
        return PJMEDIA_SDP_EINATTR;

    init_sdp_parser();


    if (attr->value.ptr[attr->value.slen] != 0 &&
	attr->value.ptr[attr->value.slen] != '\r' &&
	attr->value.ptr[attr->value.slen] != '\n')
    {
	pj_assert(!"Shouldn't happen");
	term = attr->value.ptr[attr->value.slen];
	attr->value.ptr[attr->value.slen] = '\0';
    }


    pj_scan_init(&scanner, (char*)attr->value.ptr, attr->value.slen,
		 PJ_SCAN_AUTOSKIP_WS, &on_scanner_error);


    rtpmap->pt.slen = rtpmap->param.slen = rtpmap->enc_name.slen = 0;
    rtpmap->clock_rate = 0;


    PJ_TRY {


	pj_scan_get(&scanner, &cs_token, &rtpmap->pt);


	pj_scan_get(&scanner, &cs_token, &rtpmap->enc_name);


	if (pj_scan_get_char(&scanner) != '/') {
	    status = PJMEDIA_SDP_EINRTPMAP;
	    goto on_return;
	}


	pj_scan_get(&scanner, &cs_digit, &token);
	rtpmap->clock_rate = pj_strtoul(&token);


	if (*scanner.curptr == '/') {

	    pj_scan_get_char(&scanner);
	    pj_scan_get(&scanner, &cs_token, &rtpmap->param);
	} else {
	    rtpmap->param.slen = 0;
	}

	status = PJ_SUCCESS;
    }
    PJ_CATCH_ANY {
	status = PJMEDIA_SDP_EINRTPMAP;
    }
    PJ_END;


on_return:
    pj_scan_fini(&scanner);
    if (term) {
	attr->value.ptr[attr->value.slen] = term;
    }
    return status;
}
