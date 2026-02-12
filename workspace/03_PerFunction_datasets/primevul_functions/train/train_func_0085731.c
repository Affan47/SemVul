tcp_mss(struct tcpcb *tp, int offer)
{
	struct rtentry *rt;
	struct ifnet *ifp = NULL;
	int mss, mssopt;
	int iphlen;
	struct inpcb *inp;

	inp = tp->t_inpcb;

	mssopt = mss = tcp_mssdflt;

	rt = in_pcbrtentry(inp);

	if (rt == NULL)
		goto out;

	ifp = if_get(rt->rt_ifidx);
	if (ifp == NULL)
		goto out;

	switch (tp->pf) {
#ifdef INET6
	case AF_INET6:
		iphlen = sizeof(struct ip6_hdr);
		break;
#endif
	case AF_INET:
		iphlen = sizeof(struct ip);
		break;
	default:

		goto out;
	}


	if (rt->rt_mtu) {


		if (tp->pf == AF_INET6 && rt->rt_mtu < IPV6_MMTU) {


			mss = IPV6_MMTU - iphlen - sizeof(struct ip6_frag) -
			    sizeof(struct tcphdr);
		} else {
			mss = rt->rt_mtu - iphlen -
			    sizeof(struct tcphdr);
		}
	} else if (ifp->if_flags & IFF_LOOPBACK) {
		mss = ifp->if_mtu - iphlen - sizeof(struct tcphdr);
	} else if (tp->pf == AF_INET) {
		if (ip_mtudisc)
			mss = ifp->if_mtu - iphlen - sizeof(struct tcphdr);
	}
#ifdef INET6
	else if (tp->pf == AF_INET6) {


		mss = ifp->if_mtu - iphlen - sizeof(struct tcphdr);
	}
#endif


	if (offer != -1) {
		mssopt = ifp->if_mtu - iphlen - sizeof(struct tcphdr);
		mssopt = max(tcp_mssdflt, mssopt);
	}
 out:
	if_put(ifp);


	if (offer > 0)
		tp->t_peermss = offer;
	if (tp->t_peermss)
		mss = min(mss, max(tp->t_peermss, 216));


	mss = max(mss, 64);


	tp->t_maxopd = mss;

	if ((tp->t_flags & (TF_REQ_TSTMP|TF_NOOPT)) == TF_REQ_TSTMP &&
	    (tp->t_flags & TF_RCVD_TSTMP) == TF_RCVD_TSTMP)
		mss -= TCPOLEN_TSTAMP_APPA;
#ifdef TCP_SIGNATURE
	if (tp->t_flags & TF_SIGNATURE)
		mss -= TCPOLEN_SIGLEN;
#endif

	if (offer == -1) {

		tp->t_flags &= ~TF_PMTUD_PEND;
		tp->t_pmtud_mtu_sent = 0;
		tp->t_pmtud_mss_acked = 0;
		if (mss < tp->t_maxseg) {


			tp->snd_cwnd = ulmax((tp->snd_cwnd / tp->t_maxseg) *
					     mss, mss);
		}
	} else if (tcp_do_rfc3390 == 2) {

		tp->snd_cwnd = ulmin(10 * mss, ulmax(2 * mss, 14600));
	} else if (tcp_do_rfc3390) {

		tp->snd_cwnd = ulmin(4 * mss, ulmax(2 * mss, 4380));
	} else
		tp->snd_cwnd = mss;

	tp->t_maxseg = mss;

	return (offer != -1 ? mssopt : mss);
}
