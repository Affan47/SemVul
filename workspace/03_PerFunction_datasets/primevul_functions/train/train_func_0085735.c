tcp_xmit_timer(struct tcpcb *tp, int rtt)
{
	short delta;
	short rttmin;

	if (rtt < 0)
		rtt = 0;
	else if (rtt > TCP_RTT_MAX)
		rtt = TCP_RTT_MAX;

	tcpstat_inc(tcps_rttupdated);
	if (tp->t_srtt != 0) {


		delta = (rtt << TCP_RTT_BASE_SHIFT) -
		    (tp->t_srtt >> TCP_RTT_SHIFT);
		if ((tp->t_srtt += delta) <= 0)
			tp->t_srtt = 1 << TCP_RTT_BASE_SHIFT;


		if (delta < 0)
			delta = -delta;
		delta -= (tp->t_rttvar >> TCP_RTTVAR_SHIFT);
		if ((tp->t_rttvar += delta) <= 0)
			tp->t_rttvar = 1 << TCP_RTT_BASE_SHIFT;
	} else {


		tp->t_srtt = (rtt + 1) << (TCP_RTT_SHIFT + TCP_RTT_BASE_SHIFT);
		tp->t_rttvar = (rtt + 1) <<
		    (TCP_RTTVAR_SHIFT + TCP_RTT_BASE_SHIFT - 1);
	}
	tp->t_rtttime = 0;
	tp->t_rxtshift = 0;


	rttmin = min(max(rtt + 2, tp->t_rttmin), TCPTV_REXMTMAX);
	TCPT_RANGESET(tp->t_rxtcur, TCP_REXMTVAL(tp), rttmin, TCPTV_REXMTMAX);


	tp->t_softerror = 0;
}
