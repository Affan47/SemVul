static void parse_rtcp_fb(pjmedia_rtcp_session *sess,
			  const void *pkt,
			  pj_size_t size)
{
    unsigned cnt = 1;
    pjmedia_rtcp_fb_nack nack[1];


    pjmedia_event ev;
    pj_timestamp ts_now;

    pj_get_timestamp(&ts_now);

    if (pjmedia_rtcp_fb_parse_nack(pkt, size, &cnt, nack)==PJ_SUCCESS)
    {
	pjmedia_event_init(&ev, PJMEDIA_EVENT_RX_RTCP_FB, &ts_now, sess);
	ev.data.rx_rtcp_fb.cap.type = PJMEDIA_RTCP_FB_NACK;
	ev.data.rx_rtcp_fb.msg.nack = nack[0];
	pjmedia_event_publish(NULL, sess, &ev, 0);

    } else if (pjmedia_rtcp_fb_parse_pli(pkt, size)==PJ_SUCCESS)
    {
	pjmedia_event_init(&ev, PJMEDIA_EVENT_RX_RTCP_FB, &ts_now, sess);
	ev.data.rx_rtcp_fb.cap.type = PJMEDIA_RTCP_FB_NACK;
	pj_strset2(&ev.data.rx_rtcp_fb.cap.param, (char*)"pli");
	pjmedia_event_publish(NULL, sess, &ev, 0);


    } else {

	TRACE_((sess->name, "Received unknown RTCP feedback"));
    }
}
