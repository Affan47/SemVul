PJ_DEF(void) pjmedia_rtcp_rx_rtp2(pjmedia_rtcp_session *sess,
				  unsigned seq,
				  unsigned rtp_ts,
				  unsigned payload,
				  pj_bool_t discarded)
{
    pj_timestamp ts;
    pj_uint32_t arrival;
    pj_int32_t transit;
    pjmedia_rtp_status seq_st;

#if !defined(PJMEDIA_HAS_RTCP_XR) || (PJMEDIA_HAS_RTCP_XR == 0)
    PJ_UNUSED_ARG(discarded);
#endif

    if (sess->stat.rx.pkt == 0) {

	pjmedia_rtp_seq_init(&sess->seq_ctrl, (pj_uint16_t)seq);
    }

    sess->stat.rx.pkt++;
    sess->stat.rx.bytes += payload;


    pjmedia_rtp_seq_update(&sess->seq_ctrl, (pj_uint16_t)seq, &seq_st);

    if (seq_st.status.flag.restart) {
	rtcp_init_seq(sess);
    }

    if (seq_st.status.flag.dup) {
	sess->stat.rx.dup++;
	TRACE_((sess->name, "Duplicate packet detected"));
    }

    if (seq_st.status.flag.outorder && !seq_st.status.flag.probation) {
	sess->stat.rx.reorder++;
	TRACE_((sess->name, "Out-of-order packet detected"));
    }

    if (seq_st.status.flag.bad) {
	sess->stat.rx.discard++;

#if defined(PJMEDIA_HAS_RTCP_XR) && (PJMEDIA_HAS_RTCP_XR != 0)
	pjmedia_rtcp_xr_rx_rtp(&sess->xr_session, seq,
			       -1,
			       (seq_st.status.flag.dup? 1:0),
			       (!seq_st.status.flag.dup? 1:-1),
			       -1,
			       -1, 0);
#endif

	TRACE_((sess->name, "Bad packet discarded"));
	return;
    }


    ++sess->received;


    if (seq_st.diff > 1) {
	unsigned count = seq_st.diff - 1;
	unsigned period;

	period = count * sess->pkt_size * 1000 / sess->clock_rate;
	period *= 1000;


	sess->stat.rx.loss += (seq_st.diff - 1);
	TRACE_((sess->name, "%d packet(s) lost", seq_st.diff - 1));


	pj_math_stat_update(&sess->stat.rx.loss_period, period);
    }


    if (seq_st.diff == 1 && rtp_ts != sess->rtp_last_ts) {

	pj_get_timestamp(&ts);
	ts.u64 = ts.u64 * sess->clock_rate / sess->ts_freq.u64;
	arrival = ts.u32.lo;

	transit = arrival - rtp_ts;


	if (sess->transit == 0 ||
	    sess->received < PJMEDIA_RTCP_IGNORE_FIRST_PACKETS)
	{
	    sess->transit = transit;
	    sess->stat.rx.jitter.min = (unsigned)-1;
	} else {
	    pj_int32_t d;
	    pj_uint32_t jitter;

	    d = transit - sess->transit;
	    if (d < 0)
		d = -d;

	    sess->jitter += d - ((sess->jitter + 8) >> 4);


	    jitter = sess->jitter >> 4;


	    if (jitter < 4294)
		jitter = jitter * 1000000 / sess->clock_rate;
	    else {
		jitter = jitter * 1000 / sess->clock_rate;
		jitter *= 1000;
	    }
	    pj_math_stat_update(&sess->stat.rx.jitter, jitter);


#if defined(PJMEDIA_RTCP_STAT_HAS_RAW_JITTER) && PJMEDIA_RTCP_STAT_HAS_RAW_JITTER!=0
	    {
		pj_uint32_t raw_jitter;


		if (d < 4294)
		    raw_jitter = d * 1000000 / sess->clock_rate;
		else {
		    raw_jitter = d * 1000 / sess->clock_rate;
		    raw_jitter *= 1000;
		}


		pj_math_stat_update(&sess->stat.rx_raw_jitter, raw_jitter);
	    }
#endif


#if defined(PJMEDIA_RTCP_STAT_HAS_IPDV) && PJMEDIA_RTCP_STAT_HAS_IPDV!=0
	    {
		pj_int32_t ipdv;

		ipdv = transit - sess->transit;

		if (ipdv > -2147 && ipdv < 2147)
		    ipdv = ipdv * 1000000 / (int)sess->clock_rate;
		else {
		    ipdv = ipdv * 1000 / (int)sess->clock_rate;
		    ipdv *= 1000;
		}


		pj_math_stat_update(&sess->stat.rx_ipdv, ipdv);
	    }
#endif

#if defined(PJMEDIA_HAS_RTCP_XR) && (PJMEDIA_HAS_RTCP_XR != 0)
	    pjmedia_rtcp_xr_rx_rtp(&sess->xr_session, seq,
				   0,
				   0,
				   discarded,
				   (sess->jitter >> 4),
				   -1, 0);
#endif


	    sess->transit = transit;
	}
#if defined(PJMEDIA_HAS_RTCP_XR) && (PJMEDIA_HAS_RTCP_XR != 0)
    } else if (seq_st.diff > 1) {
	int i;


	for (i=seq_st.diff-1; i>0; --i) {
	    pjmedia_rtcp_xr_rx_rtp(&sess->xr_session, seq - i,
				   1,
				   0,
				   0,
				   -1,
				   -1, 0);
	}


	pjmedia_rtcp_xr_rx_rtp(&sess->xr_session, seq,
			       0,
			       0,
			       discarded,
			       -1,
			       -1, 0);
#endif
    }


    sess->rtp_last_ts = rtp_ts;
}
