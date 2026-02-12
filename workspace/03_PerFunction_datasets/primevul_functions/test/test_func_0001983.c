static pj_uint32_t extend_seq(pjmedia_rtcp_xr_session *sess,
			      const pj_uint16_t seq)
{

    pj_uint32_t extended_seq, seq_a, seq_b, diff_a, diff_b;
    if(sess->uninitialized_src_ref_seq) {


	sess->src_ref_seq = seq | 0x80000000u;
	sess->uninitialized_src_ref_seq = PJ_FALSE;
	extended_seq = sess->src_ref_seq;
    } else {


	seq_a = seq | (sess->src_ref_seq & 0xFFFF0000u);
	if(sess->src_ref_seq < seq_a) {
	    seq_b  = seq_a - 0x00010000u;
	    diff_a = seq_a - sess->src_ref_seq;
	    diff_b = sess->src_ref_seq - seq_b;
	} else {
	    seq_b  = seq_a + 0x00010000u;
	    diff_a = sess->src_ref_seq - seq_a;
	    diff_b = seq_b - sess->src_ref_seq;
	}


	if(diff_a < diff_b) {
	    extended_seq = seq_a;
	} else {
	    extended_seq = seq_b;
	}


	sess->src_ref_seq = extended_seq;
    }


    return extended_seq;
}
