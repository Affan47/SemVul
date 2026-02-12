tcp_input(struct mbuf **mp, int *offp, int proto, int af)
{
	struct mbuf *m = *mp;
	int iphlen = *offp;
	struct ip *ip = NULL;
	struct inpcb *inp = NULL;
	u_int8_t *optp = NULL;
	int optlen = 0;
	int tlen, off;
	struct tcpcb *otp = NULL, *tp = NULL;
	int tiflags;
	struct socket *so = NULL;
	int todrop, acked, ourfinisacked;
	int hdroptlen = 0;
	short ostate;
	caddr_t saveti;
	tcp_seq iss, *reuse = NULL;
	u_long tiwin;
	struct tcp_opt_info opti;
	struct tcphdr *th;
#ifdef INET6
	struct ip6_hdr *ip6 = NULL;
#endif
#ifdef IPSEC
	struct m_tag *mtag;
	struct tdb_ident *tdbi;
	struct tdb *tdb;
	int error;
#endif
#ifdef TCP_ECN
	u_char iptos;
#endif

	tcpstat_inc(tcps_rcvtotal);

	opti.ts_present = 0;
	opti.maxseg = 0;


	if (m->m_flags & (M_BCAST|M_MCAST))
		goto drop;


	IP6_EXTHDR_GET(th, struct tcphdr *, m, iphlen, sizeof(*th));
	if (!th) {
		tcpstat_inc(tcps_rcvshort);
		return IPPROTO_DONE;
	}

	tlen = m->m_pkthdr.len - iphlen;
	switch (af) {
	case AF_INET:
		ip = mtod(m, struct ip *);
#ifdef TCP_ECN

		iptos = ip->ip_tos;
#endif
		break;
#ifdef INET6
	case AF_INET6:
		ip6 = mtod(m, struct ip6_hdr *);
#ifdef TCP_ECN
		iptos = (ntohl(ip6->ip6_flow) >> 20) & 0xff;
#endif


		if (IN6_IS_ADDR_UNSPECIFIED(&ip6->ip6_src)) {

			goto drop;
		}


		if (IN6_IS_ADDR_MULTICAST(&ip6->ip6_dst)) {

			goto drop;
		}
		break;
#endif
	default:
		unhandled_af(af);
	}


	if ((m->m_pkthdr.csum_flags & M_TCP_CSUM_IN_OK) == 0) {
		int sum;

		if (m->m_pkthdr.csum_flags & M_TCP_CSUM_IN_BAD) {
			tcpstat_inc(tcps_rcvbadsum);
			goto drop;
		}
		tcpstat_inc(tcps_inswcsum);
		switch (af) {
		case AF_INET:
			sum = in4_cksum(m, IPPROTO_TCP, iphlen, tlen);
			break;
#ifdef INET6
		case AF_INET6:
			sum = in6_cksum(m, IPPROTO_TCP, sizeof(struct ip6_hdr),
			    tlen);
			break;
#endif
		}
		if (sum != 0) {
			tcpstat_inc(tcps_rcvbadsum);
			goto drop;
		}
	}


	off = th->th_off << 2;
	if (off < sizeof(struct tcphdr) || off > tlen) {
		tcpstat_inc(tcps_rcvbadoff);
		goto drop;
	}
	tlen -= off;
	if (off > sizeof(struct tcphdr)) {
		IP6_EXTHDR_GET(th, struct tcphdr *, m, iphlen, off);
		if (!th) {
			tcpstat_inc(tcps_rcvshort);
			return IPPROTO_DONE;
		}
		optlen = off - sizeof(struct tcphdr);
		optp = (u_int8_t *)(th + 1);


		if ((optlen == TCPOLEN_TSTAMP_APPA ||
		     (optlen > TCPOLEN_TSTAMP_APPA &&
			optp[TCPOLEN_TSTAMP_APPA] == TCPOPT_EOL)) &&
		     *(u_int32_t *)optp == htonl(TCPOPT_TSTAMP_HDR) &&
		     (th->th_flags & TH_SYN) == 0) {
			opti.ts_present = 1;
			opti.ts_val = ntohl(*(u_int32_t *)(optp + 4));
			opti.ts_ecr = ntohl(*(u_int32_t *)(optp + 8));
			optp = NULL;
		}
	}
	tiflags = th->th_flags;


	th->th_seq = ntohl(th->th_seq);
	th->th_ack = ntohl(th->th_ack);
	th->th_win = ntohs(th->th_win);
	th->th_urp = ntohs(th->th_urp);


#if NPF > 0
	inp = pf_inp_lookup(m);
#endif
findpcb:
	if (inp == NULL) {
		switch (af) {
#ifdef INET6
		case AF_INET6:
			inp = in6_pcbhashlookup(&tcbtable, &ip6->ip6_src,
			    th->th_sport, &ip6->ip6_dst, th->th_dport,
			    m->m_pkthdr.ph_rtableid);
			break;
#endif
		case AF_INET:
			inp = in_pcbhashlookup(&tcbtable, ip->ip_src,
			    th->th_sport, ip->ip_dst, th->th_dport,
			    m->m_pkthdr.ph_rtableid);
			break;
		}
	}
	if (inp == NULL) {
		tcpstat_inc(tcps_pcbhashmiss);
		switch (af) {
#ifdef INET6
		case AF_INET6:
			inp = in6_pcblookup_listen(&tcbtable, &ip6->ip6_dst,
			    th->th_dport, m, m->m_pkthdr.ph_rtableid);
			break;
#endif
		case AF_INET:
			inp = in_pcblookup_listen(&tcbtable, ip->ip_dst,
			    th->th_dport, m, m->m_pkthdr.ph_rtableid);
			break;
		}


		if (inp == NULL) {
			tcpstat_inc(tcps_noport);
			goto dropwithreset_ratelim;
		}
	}
	KASSERT(sotoinpcb(inp->inp_socket) == inp);
	KASSERT(intotcpcb(inp) == NULL || intotcpcb(inp)->t_inpcb == inp);
	soassertlocked(inp->inp_socket);


	switch (af) {
	case AF_INET:
		if (inp->inp_ip_minttl && inp->inp_ip_minttl > ip->ip_ttl)
			goto drop;
		break;
#ifdef INET6
	case AF_INET6:
		if (inp->inp_ip6_minhlim &&
		    inp->inp_ip6_minhlim > ip6->ip6_hlim)
			goto drop;
		break;
#endif
	}

	tp = intotcpcb(inp);
	if (tp == NULL)
		goto dropwithreset_ratelim;
	if (tp->t_state == TCPS_CLOSED)
		goto drop;


	if ((tiflags & TH_SYN) == 0)
		tiwin = th->th_win << tp->snd_scale;
	else
		tiwin = th->th_win;

	so = inp->inp_socket;
	if (so->so_options & (SO_DEBUG|SO_ACCEPTCONN)) {
		union syn_cache_sa src;
		union syn_cache_sa dst;

		bzero(&src, sizeof(src));
		bzero(&dst, sizeof(dst));
		switch (af) {
		case AF_INET:
			src.sin.sin_len = sizeof(struct sockaddr_in);
			src.sin.sin_family = AF_INET;
			src.sin.sin_addr = ip->ip_src;
			src.sin.sin_port = th->th_sport;

			dst.sin.sin_len = sizeof(struct sockaddr_in);
			dst.sin.sin_family = AF_INET;
			dst.sin.sin_addr = ip->ip_dst;
			dst.sin.sin_port = th->th_dport;
			break;
#ifdef INET6
		case AF_INET6:
			src.sin6.sin6_len = sizeof(struct sockaddr_in6);
			src.sin6.sin6_family = AF_INET6;
			src.sin6.sin6_addr = ip6->ip6_src;
			src.sin6.sin6_port = th->th_sport;

			dst.sin6.sin6_len = sizeof(struct sockaddr_in6);
			dst.sin6.sin6_family = AF_INET6;
			dst.sin6.sin6_addr = ip6->ip6_dst;
			dst.sin6.sin6_port = th->th_dport;
			break;
#endif
		}

		if (so->so_options & SO_DEBUG) {
			otp = tp;
			ostate = tp->t_state;
			switch (af) {
#ifdef INET6
			case AF_INET6:
				saveti = (caddr_t) &tcp_saveti6;
				memcpy(&tcp_saveti6.ti6_i, ip6, sizeof(*ip6));
				memcpy(&tcp_saveti6.ti6_t, th, sizeof(*th));
				break;
#endif
			case AF_INET:
				saveti = (caddr_t) &tcp_saveti;
				memcpy(&tcp_saveti.ti_i, ip, sizeof(*ip));
				memcpy(&tcp_saveti.ti_t, th, sizeof(*th));
				break;
			}
		}
		if (so->so_options & SO_ACCEPTCONN) {
			switch (tiflags & (TH_RST|TH_SYN|TH_ACK)) {

			case TH_SYN|TH_ACK|TH_RST:
			case TH_SYN|TH_RST:
			case TH_ACK|TH_RST:
			case TH_RST:
				syn_cache_reset(&src.sa, &dst.sa, th,
				    inp->inp_rtableid);
				goto drop;

			case TH_SYN|TH_ACK:


				goto badsyn;

			case TH_ACK:
				so = syn_cache_get(&src.sa, &dst.sa,
					th, iphlen, tlen, so, m);
				if (so == NULL) {


					goto badsyn;
				} else if (so == (struct socket *)(-1)) {


					m = *mp = NULL;
					goto drop;
				} else {


					tp = NULL;
					inp = sotoinpcb(so);
					tp = intotcpcb(inp);
					if (tp == NULL)
						goto badsyn;

				}
				break;

			default:


				goto badsyn;

			case TH_SYN:


#ifdef INET6


				if (ip6 && !ip6_use_deprecated) {
					struct in6_ifaddr *ia6;
					struct ifnet *ifp =
					    if_get(m->m_pkthdr.ph_ifidx);

					if (ifp &&
					    (ia6 = in6ifa_ifpwithaddr(ifp,
					    &ip6->ip6_dst)) &&
					    (ia6->ia6_flags &
					    IN6_IFF_DEPRECATED)) {
						tp = NULL;
						if_put(ifp);
						goto dropwithreset;
					}
					if_put(ifp);
				}
#endif


				if (th->th_dport == th->th_sport) {
					switch (af) {
#ifdef INET6
					case AF_INET6:
						if (IN6_ARE_ADDR_EQUAL(&ip6->ip6_src,
						    &ip6->ip6_dst)) {
							tcpstat_inc(tcps_badsyn);
							goto drop;
						}
						break;
#endif
					case AF_INET:
						if (ip->ip_dst.s_addr == ip->ip_src.s_addr) {
							tcpstat_inc(tcps_badsyn);
							goto drop;
						}
						break;
					}
				}


				if (so->so_qlen > so->so_qlimit ||
				    syn_cache_add(&src.sa, &dst.sa, th, iphlen,
				    so, m, optp, optlen, &opti, reuse) == -1) {
					tcpstat_inc(tcps_dropsyn);
					goto drop;
				}
				return IPPROTO_DONE;
			}
		}
	}

#ifdef DIAGNOSTIC


	if (tp->t_state == TCPS_LISTEN)
		panic("tcp_input: TCPS_LISTEN");
#endif

#if NPF > 0
	pf_inp_link(m, inp);
#endif

#ifdef IPSEC

	mtag = m_tag_find(m, PACKET_TAG_IPSEC_IN_DONE, NULL);
	if (mtag != NULL) {
		tdbi = (struct tdb_ident *)(mtag + 1);
	        tdb = gettdb(tdbi->rdomain, tdbi->spi,
		    &tdbi->dst, tdbi->proto);
	} else
		tdb = NULL;
	ipsp_spd_lookup(m, af, iphlen, &error, IPSP_DIRECTION_IN,
	    tdb, inp, 0);
	if (error) {
		tcpstat_inc(tcps_rcvnosec);
		goto drop;
	}
#endif


	tp->t_rcvtime = tcp_now;
	if (TCPS_HAVEESTABLISHED(tp->t_state))
		TCP_TIMER_ARM(tp, TCPT_KEEP, tcp_keepidle);

	if (tp->sack_enable)
		tcp_del_sackholes(tp, th);


#ifdef TCP_SIGNATURE
	if (optp || (tp->t_flags & TF_SIGNATURE))
#else
	if (optp)
#endif
		if (tcp_dooptions(tp, optp, optlen, th, m, iphlen, &opti,
		    m->m_pkthdr.ph_rtableid))
			goto drop;

	if (opti.ts_present && opti.ts_ecr) {
		int rtt_test;


		opti.ts_ecr -= tp->ts_modulate;


		rtt_test = tcp_now - opti.ts_ecr;
		if (rtt_test < 0 || rtt_test > TCP_RTT_MAX)
			opti.ts_ecr = 0;
	}

#ifdef TCP_ECN

	if ((iptos & IPTOS_ECN_MASK) == IPTOS_ECN_CE) {
		tp->t_flags |= TF_RCVD_CE;
		tcpstat_inc(tcps_ecn_rcvce);
	}
#endif


	if (tp->t_state == TCPS_ESTABLISHED &&
#ifdef TCP_ECN
	    (tiflags & (TH_SYN|TH_FIN|TH_RST|TH_URG|TH_ECE|TH_CWR|TH_ACK)) == TH_ACK &&
#else
	    (tiflags & (TH_SYN|TH_FIN|TH_RST|TH_URG|TH_ACK)) == TH_ACK &&
#endif
	    (!opti.ts_present || TSTMP_GEQ(opti.ts_val, tp->ts_recent)) &&
	    th->th_seq == tp->rcv_nxt &&
	    tiwin && tiwin == tp->snd_wnd &&
	    tp->snd_nxt == tp->snd_max) {


		if (opti.ts_present && SEQ_LEQ(th->th_seq, tp->last_ack_sent)) {
			tp->ts_recent_age = tcp_now;
			tp->ts_recent = opti.ts_val;
		}

		if (tlen == 0) {
			if (SEQ_GT(th->th_ack, tp->snd_una) &&
			    SEQ_LEQ(th->th_ack, tp->snd_max) &&
			    tp->snd_cwnd >= tp->snd_wnd &&
			    tp->t_dupacks == 0) {


				tcpstat_inc(tcps_predack);
				if (opti.ts_present && opti.ts_ecr)
					tcp_xmit_timer(tp, tcp_now - opti.ts_ecr);
				else if (tp->t_rtttime &&
				    SEQ_GT(th->th_ack, tp->t_rtseq))
					tcp_xmit_timer(tp,
					    tcp_now - tp->t_rtttime);
				acked = th->th_ack - tp->snd_una;
				tcpstat_pkt(tcps_rcvackpack, tcps_rcvackbyte,
				    acked);
				ND6_HINT(tp);
				sbdrop(so, &so->so_snd, acked);


				if ((tp->t_flags & TF_PMTUD_PEND) &&
				    SEQ_GT(th->th_ack, tp->t_pmtud_th_seq))
					tp->t_flags &= ~TF_PMTUD_PEND;


				if (tp->t_pmtud_mss_acked < acked)
					tp->t_pmtud_mss_acked = acked;

				tp->snd_una = th->th_ack;


#ifdef TCP_ECN
				if (SEQ_GT(tp->snd_una, tp->snd_last))
#endif
				tp->snd_last = tp->snd_una;
				m_freem(m);


				if (tp->snd_una == tp->snd_max)
					TCP_TIMER_DISARM(tp, TCPT_REXMT);
				else if (TCP_TIMER_ISARMED(tp, TCPT_PERSIST) == 0)
					TCP_TIMER_ARM(tp, TCPT_REXMT, tp->t_rxtcur);

				tcp_update_sndspace(tp);
				if (sb_notify(so, &so->so_snd)) {
					tp->t_flags |= TF_BLOCKOUTPUT;
					sowwakeup(so);
					tp->t_flags &= ~TF_BLOCKOUTPUT;
				}
				if (so->so_snd.sb_cc ||
				    tp->t_flags & TF_NEEDOUTPUT)
					(void) tcp_output(tp);
				return IPPROTO_DONE;
			}
		} else if (th->th_ack == tp->snd_una &&
		    TAILQ_EMPTY(&tp->t_segq) &&
		    tlen <= sbspace(so, &so->so_rcv)) {


			if (tp->sack_enable && tp->rcv_numsacks)
				tcp_clean_sackreport(tp);
			tcpstat_inc(tcps_preddat);
			tp->rcv_nxt += tlen;
			tcpstat_pkt(tcps_rcvpack, tcps_rcvbyte, tlen);
			ND6_HINT(tp);

			TCP_SETUP_ACK(tp, tiflags, m);


			if (so->so_state & SS_CANTRCVMORE)
				m_freem(m);
			else {
				if (opti.ts_present && opti.ts_ecr) {
					if (tp->rfbuf_ts < opti.ts_ecr &&
					    opti.ts_ecr - tp->rfbuf_ts < hz) {
						tcp_update_rcvspace(tp);

						tp->rfbuf_cnt = 0;
						tp->rfbuf_ts = 0;
					} else
						tp->rfbuf_cnt += tlen;
				}
				m_adj(m, iphlen + off);
				sbappendstream(so, &so->so_rcv, m);
			}
			tp->t_flags |= TF_BLOCKOUTPUT;
			sorwakeup(so);
			tp->t_flags &= ~TF_BLOCKOUTPUT;
			if (tp->t_flags & (TF_ACKNOW|TF_NEEDOUTPUT))
				(void) tcp_output(tp);
			return IPPROTO_DONE;
		}
	}


	hdroptlen = iphlen + off;


	{ int win;

	win = sbspace(so, &so->so_rcv);
	if (win < 0)
		win = 0;
	tp->rcv_wnd = imax(win, (int)(tp->rcv_adv - tp->rcv_nxt));
	}


	tp->rfbuf_cnt = 0;
	tp->rfbuf_ts = 0;

	switch (tp->t_state) {


	case TCPS_SYN_RECEIVED:
		if (tiflags & TH_ACK) {
			if (tiflags & TH_SYN) {
				tcpstat_inc(tcps_badsyn);
				goto dropwithreset;
			}
			if (SEQ_LEQ(th->th_ack, tp->snd_una) ||
			    SEQ_GT(th->th_ack, tp->snd_max))
				goto dropwithreset;
		}
		break;


	case TCPS_SYN_SENT:
		if ((tiflags & TH_ACK) &&
		    (SEQ_LEQ(th->th_ack, tp->iss) ||
		     SEQ_GT(th->th_ack, tp->snd_max)))
			goto dropwithreset;
		if (tiflags & TH_RST) {
#ifdef TCP_ECN

			if (tcp_do_ecn && !(tp->t_flags & TF_DISABLE_ECN))
				goto drop;
#endif
			if (tiflags & TH_ACK)
				tp = tcp_drop(tp, ECONNREFUSED);
			goto drop;
		}
		if ((tiflags & TH_SYN) == 0)
			goto drop;
		if (tiflags & TH_ACK) {
			tp->snd_una = th->th_ack;
			if (SEQ_LT(tp->snd_nxt, tp->snd_una))
				tp->snd_nxt = tp->snd_una;
		}
		TCP_TIMER_DISARM(tp, TCPT_REXMT);
		tp->irs = th->th_seq;
		tcp_mss(tp, opti.maxseg);

		if (tp->t_rxtshift > 0)
			tp->snd_cwnd = tp->t_maxseg;
		tcp_rcvseqinit(tp);
		tp->t_flags |= TF_ACKNOW;


		if (tp->sack_enable)
			tp->sack_enable = tp->t_flags & TF_SACK_PERMIT;
#ifdef TCP_ECN


		if (tcp_do_ecn) {
			switch (tiflags & (TH_ACK|TH_ECE|TH_CWR)) {
			case TH_ACK|TH_ECE:
			case TH_ECE|TH_CWR:
				tp->t_flags |= TF_ECN_PERMIT;
				tiflags &= ~(TH_ECE|TH_CWR);
				tcpstat_inc(tcps_ecn_accepts);
			}
		}
#endif

		if (tiflags & TH_ACK && SEQ_GT(tp->snd_una, tp->iss)) {
			tcpstat_inc(tcps_connects);
			tp->t_flags |= TF_BLOCKOUTPUT;
			soisconnected(so);
			tp->t_flags &= ~TF_BLOCKOUTPUT;
			tp->t_state = TCPS_ESTABLISHED;
			TCP_TIMER_ARM(tp, TCPT_KEEP, tcp_keepidle);

			if ((tp->t_flags & (TF_RCVD_SCALE|TF_REQ_SCALE)) ==
				(TF_RCVD_SCALE|TF_REQ_SCALE)) {
				tp->snd_scale = tp->requested_s_scale;
				tp->rcv_scale = tp->request_r_scale;
			}
			tcp_flush_queue(tp);


			if (tp->t_rtttime)
				tcp_xmit_timer(tp, tcp_now - tp->t_rtttime);


			tp->snd_cwnd += tp->t_maxseg;
		} else
			tp->t_state = TCPS_SYN_RECEIVED;

#if 0
trimthenstep6:
#endif


		th->th_seq++;
		if (tlen > tp->rcv_wnd) {
			todrop = tlen - tp->rcv_wnd;
			m_adj(m, -todrop);
			tlen = tp->rcv_wnd;
			tiflags &= ~TH_FIN;
			tcpstat_pkt(tcps_rcvpackafterwin, tcps_rcvbyteafterwin,
			    todrop);
		}
		tp->snd_wl1 = th->th_seq - 1;
		tp->rcv_up = th->th_seq;
		goto step6;


	case TCPS_TIME_WAIT:
		if (((tiflags & (TH_SYN|TH_ACK)) == TH_SYN) &&
		    ((opti.ts_present &&
		    TSTMP_LT(tp->ts_recent, opti.ts_val)) ||
		    SEQ_GT(th->th_seq, tp->rcv_nxt))) {
#if NPF > 0


			pf_inp_unlink(inp);
#endif


			iss = tp->snd_nxt +
			    ((arc4random() & 0x7fffffff) | 0x8000);
			reuse = &iss;
			tp = tcp_close(tp);
			inp = NULL;
			goto findpcb;
		}
	}


	if (opti.ts_present && (tiflags & TH_RST) == 0 && tp->ts_recent &&
	    TSTMP_LT(opti.ts_val, tp->ts_recent)) {


		if ((int)(tcp_now - tp->ts_recent_age) > TCP_PAWS_IDLE) {


			tp->ts_recent = 0;
		} else {
			tcpstat_pkt(tcps_rcvduppack, tcps_rcvdupbyte, tlen);
			tcpstat_inc(tcps_pawsdrop);
			if (tlen)
				goto dropafterack;
			goto drop;
		}
	}

	todrop = tp->rcv_nxt - th->th_seq;
	if (todrop > 0) {
		if (tiflags & TH_SYN) {
			tiflags &= ~TH_SYN;
			th->th_seq++;
			if (th->th_urp > 1)
				th->th_urp--;
			else
				tiflags &= ~TH_URG;
			todrop--;
		}
		if (todrop > tlen ||
		    (todrop == tlen && (tiflags & TH_FIN) == 0)) {


			tiflags &= ~TH_FIN;


			tp->t_flags |= TF_ACKNOW;
			todrop = tlen;
			tcpstat_pkt(tcps_rcvduppack, tcps_rcvdupbyte, todrop);
		} else {
			tcpstat_pkt(tcps_rcvpartduppack, tcps_rcvpartdupbyte,
			    todrop);
		}
		hdroptlen += todrop;
		th->th_seq += todrop;
		tlen -= todrop;
		if (th->th_urp > todrop)
			th->th_urp -= todrop;
		else {
			tiflags &= ~TH_URG;
			th->th_urp = 0;
		}
	}


	if ((so->so_state & SS_NOFDREF) &&
	    tp->t_state > TCPS_CLOSE_WAIT && tlen) {
		tp = tcp_close(tp);
		tcpstat_inc(tcps_rcvafterclose);
		goto dropwithreset;
	}


	todrop = (th->th_seq + tlen) - (tp->rcv_nxt+tp->rcv_wnd);
	if (todrop > 0) {
		tcpstat_inc(tcps_rcvpackafterwin);
		if (todrop >= tlen) {
			tcpstat_add(tcps_rcvbyteafterwin, tlen);


			if (tp->rcv_wnd == 0 && th->th_seq == tp->rcv_nxt) {
				tp->t_flags |= TF_ACKNOW;
				tcpstat_inc(tcps_rcvwinprobe);
			} else
				goto dropafterack;
		} else
			tcpstat_add(tcps_rcvbyteafterwin, todrop);
		m_adj(m, -todrop);
		tlen -= todrop;
		tiflags &= ~(TH_PUSH|TH_FIN);
	}


	if (opti.ts_present && TSTMP_GEQ(opti.ts_val, tp->ts_recent) &&
	    SEQ_LEQ(th->th_seq, tp->last_ack_sent)) {
		tp->ts_recent_age = tcp_now;
		tp->ts_recent = opti.ts_val;
	}


	if (tiflags & TH_RST) {
		if (th->th_seq != tp->last_ack_sent &&
		    th->th_seq != tp->rcv_nxt &&
		    th->th_seq != (tp->rcv_nxt + 1))
			goto drop;

		switch (tp->t_state) {
		case TCPS_SYN_RECEIVED:
#ifdef TCP_ECN

			if (tcp_do_ecn && !(tp->t_flags & TF_DISABLE_ECN))
				goto drop;
#endif
			so->so_error = ECONNREFUSED;
			goto close;

		case TCPS_ESTABLISHED:
		case TCPS_FIN_WAIT_1:
		case TCPS_FIN_WAIT_2:
		case TCPS_CLOSE_WAIT:
			so->so_error = ECONNRESET;
		close:
			tp->t_state = TCPS_CLOSED;
			tcpstat_inc(tcps_drops);
			tp = tcp_close(tp);
			goto drop;
		case TCPS_CLOSING:
		case TCPS_LAST_ACK:
		case TCPS_TIME_WAIT:
			tp = tcp_close(tp);
			goto drop;
		}
	}


	if (tiflags & TH_SYN)
		goto dropafterack_ratelim;


	if ((tiflags & TH_ACK) == 0) {
		if (tp->t_flags & TF_ACKNOW)
			goto dropafterack;
		else
			goto drop;
	}


	switch (tp->t_state) {


	case TCPS_SYN_RECEIVED:
		tcpstat_inc(tcps_connects);
		tp->t_flags |= TF_BLOCKOUTPUT;
		soisconnected(so);
		tp->t_flags &= ~TF_BLOCKOUTPUT;
		tp->t_state = TCPS_ESTABLISHED;
		TCP_TIMER_ARM(tp, TCPT_KEEP, tcp_keepidle);

		if ((tp->t_flags & (TF_RCVD_SCALE|TF_REQ_SCALE)) ==
			(TF_RCVD_SCALE|TF_REQ_SCALE)) {
			tp->snd_scale = tp->requested_s_scale;
			tp->rcv_scale = tp->request_r_scale;
			tiwin = th->th_win << tp->snd_scale;
		}
		tcp_flush_queue(tp);
		tp->snd_wl1 = th->th_seq - 1;


	case TCPS_ESTABLISHED:
	case TCPS_FIN_WAIT_1:
	case TCPS_FIN_WAIT_2:
	case TCPS_CLOSE_WAIT:
	case TCPS_CLOSING:
	case TCPS_LAST_ACK:
	case TCPS_TIME_WAIT:
#ifdef TCP_ECN


		if (tcp_do_ecn && (tiflags & TH_ECE)) {
			if ((tp->t_flags & TF_ECN_PERMIT) &&
			    SEQ_GEQ(tp->snd_una, tp->snd_last)) {
				u_int win;

				win = min(tp->snd_wnd, tp->snd_cwnd) / tp->t_maxseg;
				if (win > 1) {
					tp->snd_ssthresh = win / 2 * tp->t_maxseg;
					tp->snd_cwnd = tp->snd_ssthresh;
					tp->snd_last = tp->snd_max;
					tp->t_flags |= TF_SEND_CWR;
					tcpstat_inc(tcps_cwr_ecn);
				}
			}
			tcpstat_inc(tcps_ecn_rcvece);
		}


		if ((tiflags & TH_CWR)) {
			tp->t_flags &= ~TF_RCVD_CE;
			tcpstat_inc(tcps_ecn_rcvcwr);
		}
#endif

		if (SEQ_LEQ(th->th_ack, tp->snd_una)) {


			if (tlen) {

				if (th->th_seq != tp->rcv_nxt &&
				   SEQ_LT(th->th_ack,
				   tp->snd_una - tp->max_sndwnd)) {
					tcpstat_inc(tcps_rcvacktooold);
					goto drop;
				}
				break;
			}


			if (th->th_ack != tp->snd_una) {
				tp->t_dupacks = 0;
				break;
			}
			if (tiwin == tp->snd_wnd) {
				tcpstat_inc(tcps_rcvdupack);


				if (TCP_TIMER_ISARMED(tp, TCPT_REXMT) == 0)
					tp->t_dupacks = 0;
				else if (++tp->t_dupacks == tcprexmtthresh) {
					tcp_seq onxt = tp->snd_nxt;
					u_long win =
					    ulmin(tp->snd_wnd, tp->snd_cwnd) /
						2 / tp->t_maxseg;

					if (SEQ_LT(th->th_ack, tp->snd_last)){


						tp->t_dupacks = 0;
						goto drop;
					}
					if (win < 2)
						win = 2;
					tp->snd_ssthresh = win * tp->t_maxseg;
					tp->snd_last = tp->snd_max;
					if (tp->sack_enable) {
						TCP_TIMER_DISARM(tp, TCPT_REXMT);
						tp->t_rtttime = 0;
#ifdef TCP_ECN
						tp->t_flags |= TF_SEND_CWR;
#endif
						tcpstat_inc(tcps_cwr_frecovery);
						tcpstat_inc(tcps_sack_recovery_episode);


						(void) tcp_output(tp);
						tp->snd_cwnd = tp->snd_ssthresh+
					           tp->t_maxseg * tp->t_dupacks;
						goto drop;
					}
					TCP_TIMER_DISARM(tp, TCPT_REXMT);
					tp->t_rtttime = 0;
					tp->snd_nxt = th->th_ack;
					tp->snd_cwnd = tp->t_maxseg;
#ifdef TCP_ECN
					tp->t_flags |= TF_SEND_CWR;
#endif
					tcpstat_inc(tcps_cwr_frecovery);
					tcpstat_inc(tcps_sndrexmitfast);
					(void) tcp_output(tp);

					tp->snd_cwnd = tp->snd_ssthresh +
					    tp->t_maxseg * tp->t_dupacks;
					if (SEQ_GT(onxt, tp->snd_nxt))
						tp->snd_nxt = onxt;
					goto drop;
				} else if (tp->t_dupacks > tcprexmtthresh) {
					tp->snd_cwnd += tp->t_maxseg;
					(void) tcp_output(tp);
					goto drop;
				}
			} else if (tiwin < tp->snd_wnd) {


				tp->t_dupacks = 0;
			}
			break;
		}


		if (tp->t_dupacks >= tcprexmtthresh) {

			if (SEQ_LT(th->th_ack, tp->snd_last)) {
				if (tp->sack_enable)
					tcp_sack_partialack(tp, th);
				else
					tcp_newreno_partialack(tp, th);
			} else {

				tp->snd_cwnd = tp->snd_ssthresh;
				if (tcp_seq_subtract(tp->snd_max, th->th_ack) <
				    tp->snd_ssthresh)
					tp->snd_cwnd =
					    tcp_seq_subtract(tp->snd_max,
					    th->th_ack);
				tp->t_dupacks = 0;
			}
		} else {


			tp->t_dupacks = 0;
		}
		if (SEQ_GT(th->th_ack, tp->snd_max)) {
			tcpstat_inc(tcps_rcvacktoomuch);
			goto dropafterack_ratelim;
		}
		acked = th->th_ack - tp->snd_una;
		tcpstat_pkt(tcps_rcvackpack, tcps_rcvackbyte, acked);


		if (opti.ts_present && opti.ts_ecr)
			tcp_xmit_timer(tp, tcp_now - opti.ts_ecr);
		else if (tp->t_rtttime && SEQ_GT(th->th_ack, tp->t_rtseq))
			tcp_xmit_timer(tp, tcp_now - tp->t_rtttime);


		if (th->th_ack == tp->snd_max) {
			TCP_TIMER_DISARM(tp, TCPT_REXMT);
			tp->t_flags |= TF_NEEDOUTPUT;
		} else if (TCP_TIMER_ISARMED(tp, TCPT_PERSIST) == 0)
			TCP_TIMER_ARM(tp, TCPT_REXMT, tp->t_rxtcur);


		{
		u_int cw = tp->snd_cwnd;
		u_int incr = tp->t_maxseg;

		if (cw > tp->snd_ssthresh)
			incr = incr * incr / cw;
		if (tp->t_dupacks < tcprexmtthresh)
			tp->snd_cwnd = ulmin(cw + incr,
			    TCP_MAXWIN << tp->snd_scale);
		}
		ND6_HINT(tp);
		if (acked > so->so_snd.sb_cc) {
			tp->snd_wnd -= so->so_snd.sb_cc;
			sbdrop(so, &so->so_snd, (int)so->so_snd.sb_cc);
			ourfinisacked = 1;
		} else {
			sbdrop(so, &so->so_snd, acked);
			tp->snd_wnd -= acked;
			ourfinisacked = 0;
		}

		tcp_update_sndspace(tp);
		if (sb_notify(so, &so->so_snd)) {
			tp->t_flags |= TF_BLOCKOUTPUT;
			sowwakeup(so);
			tp->t_flags &= ~TF_BLOCKOUTPUT;
		}


		if ((tp->t_flags & TF_PMTUD_PEND) &&
		    SEQ_GT(th->th_ack, tp->t_pmtud_th_seq))
			tp->t_flags &= ~TF_PMTUD_PEND;


		if (tp->t_pmtud_mss_acked < acked)
			tp->t_pmtud_mss_acked = acked;

		tp->snd_una = th->th_ack;
#ifdef TCP_ECN

		if (SEQ_GT(tp->snd_una, tp->snd_last))
			tp->snd_last = tp->snd_una;
#endif
		if (SEQ_LT(tp->snd_nxt, tp->snd_una))
			tp->snd_nxt = tp->snd_una;

		switch (tp->t_state) {


		case TCPS_FIN_WAIT_1:
			if (ourfinisacked) {


				if (so->so_state & SS_CANTRCVMORE) {
					tp->t_flags |= TF_BLOCKOUTPUT;
					soisdisconnected(so);
					tp->t_flags &= ~TF_BLOCKOUTPUT;
					TCP_TIMER_ARM(tp, TCPT_2MSL, tcp_maxidle);
				}
				tp->t_state = TCPS_FIN_WAIT_2;
			}
			break;


		case TCPS_CLOSING:
			if (ourfinisacked) {
				tp->t_state = TCPS_TIME_WAIT;
				tcp_canceltimers(tp);
				TCP_TIMER_ARM(tp, TCPT_2MSL, 2 * TCPTV_MSL);
				tp->t_flags |= TF_BLOCKOUTPUT;
				soisdisconnected(so);
				tp->t_flags &= ~TF_BLOCKOUTPUT;
			}
			break;


		case TCPS_LAST_ACK:
			if (ourfinisacked) {
				tp = tcp_close(tp);
				goto drop;
			}
			break;


		case TCPS_TIME_WAIT:
			TCP_TIMER_ARM(tp, TCPT_2MSL, 2 * TCPTV_MSL);
			goto dropafterack;
		}
	}

step6:


	if ((tiflags & TH_ACK) &&
	    (SEQ_LT(tp->snd_wl1, th->th_seq) || (tp->snd_wl1 == th->th_seq &&
	    (SEQ_LT(tp->snd_wl2, th->th_ack) ||
	    (tp->snd_wl2 == th->th_ack && tiwin > tp->snd_wnd))))) {

		if (tlen == 0 &&
		    tp->snd_wl2 == th->th_ack && tiwin > tp->snd_wnd)
			tcpstat_inc(tcps_rcvwinupd);
		tp->snd_wnd = tiwin;
		tp->snd_wl1 = th->th_seq;
		tp->snd_wl2 = th->th_ack;
		if (tp->snd_wnd > tp->max_sndwnd)
			tp->max_sndwnd = tp->snd_wnd;
		tp->t_flags |= TF_NEEDOUTPUT;
	}


	if ((tiflags & TH_URG) && th->th_urp &&
	    TCPS_HAVERCVDFIN(tp->t_state) == 0) {


		if (th->th_urp + so->so_rcv.sb_cc > sb_max) {
			th->th_urp = 0;
			tiflags &= ~TH_URG;
			goto dodata;
		}


		if (SEQ_GT(th->th_seq+th->th_urp, tp->rcv_up)) {
			tp->rcv_up = th->th_seq + th->th_urp;
			so->so_oobmark = so->so_rcv.sb_cc +
			    (tp->rcv_up - tp->rcv_nxt) - 1;
			if (so->so_oobmark == 0)
				so->so_state |= SS_RCVATMARK;
			sohasoutofband(so);
			tp->t_oobflags &= ~(TCPOOB_HAVEDATA | TCPOOB_HADDATA);
		}


		if (th->th_urp <= (u_int16_t) tlen &&
		    (so->so_options & SO_OOBINLINE) == 0)
		        tcp_pulloutofband(so, th->th_urp, m, hdroptlen);
	} else


		if (SEQ_GT(tp->rcv_nxt, tp->rcv_up))
			tp->rcv_up = tp->rcv_nxt;
dodata:


	if ((tlen || (tiflags & TH_FIN)) &&
	    TCPS_HAVERCVDFIN(tp->t_state) == 0) {
		tcp_seq laststart = th->th_seq;
		tcp_seq lastend = th->th_seq + tlen;

		if (th->th_seq == tp->rcv_nxt && TAILQ_EMPTY(&tp->t_segq) &&
		    tp->t_state == TCPS_ESTABLISHED) {
			TCP_SETUP_ACK(tp, tiflags, m);
			tp->rcv_nxt += tlen;
			tiflags = th->th_flags & TH_FIN;
			tcpstat_pkt(tcps_rcvpack, tcps_rcvbyte, tlen);
			ND6_HINT(tp);
			if (so->so_state & SS_CANTRCVMORE)
				m_freem(m);
			else {
				m_adj(m, hdroptlen);
				sbappendstream(so, &so->so_rcv, m);
			}
			tp->t_flags |= TF_BLOCKOUTPUT;
			sorwakeup(so);
			tp->t_flags &= ~TF_BLOCKOUTPUT;
		} else {
			m_adj(m, hdroptlen);
			tiflags = tcp_reass(tp, th, m, &tlen);
			tp->t_flags |= TF_ACKNOW;
		}
		if (tp->sack_enable)
			tcp_update_sack_list(tp, laststart, lastend);


#if 0


		len = so->so_rcv.sb_hiwat - (tp->rcv_adv - tp->rcv_nxt);
#endif
	} else {
		m_freem(m);
		tiflags &= ~TH_FIN;
	}


	if ((tiflags & TH_FIN) && TCPS_HAVEESTABLISHED(tp->t_state)) {
		if (TCPS_HAVERCVDFIN(tp->t_state) == 0) {
			tp->t_flags |= TF_BLOCKOUTPUT;
			socantrcvmore(so);
			tp->t_flags &= ~TF_BLOCKOUTPUT;
			tp->t_flags |= TF_ACKNOW;
			tp->rcv_nxt++;
		}
		switch (tp->t_state) {


		case TCPS_ESTABLISHED:
			tp->t_state = TCPS_CLOSE_WAIT;
			break;


		case TCPS_FIN_WAIT_1:
			tp->t_state = TCPS_CLOSING;
			break;


		case TCPS_FIN_WAIT_2:
			tp->t_state = TCPS_TIME_WAIT;
			tcp_canceltimers(tp);
			TCP_TIMER_ARM(tp, TCPT_2MSL, 2 * TCPTV_MSL);
			tp->t_flags |= TF_BLOCKOUTPUT;
			soisdisconnected(so);
			tp->t_flags &= ~TF_BLOCKOUTPUT;
			break;


		case TCPS_TIME_WAIT:
			TCP_TIMER_ARM(tp, TCPT_2MSL, 2 * TCPTV_MSL);
			break;
		}
	}
	if (otp)
		tcp_trace(TA_INPUT, ostate, tp, otp, saveti, 0, tlen);


	if (tp->t_flags & (TF_ACKNOW|TF_NEEDOUTPUT))
		(void) tcp_output(tp);
	return IPPROTO_DONE;

badsyn:


	tcpstat_inc(tcps_badsyn);
	tp = NULL;
	goto dropwithreset;

dropafterack_ratelim:
	if (ppsratecheck(&tcp_ackdrop_ppslim_last, &tcp_ackdrop_ppslim_count,
	    tcp_ackdrop_ppslim) == 0) {

		goto drop;
	}


dropafterack:


	if (tiflags & TH_RST)
		goto drop;
	m_freem(m);
	tp->t_flags |= TF_ACKNOW;
	(void) tcp_output(tp);
	return IPPROTO_DONE;

dropwithreset_ratelim:


	if (ppsratecheck(&tcp_rst_ppslim_last, &tcp_rst_ppslim_count,
	    tcp_rst_ppslim) == 0) {

		goto drop;
	}


dropwithreset:


	if (tiflags & TH_RST)
		goto drop;
	if (tiflags & TH_ACK) {
		tcp_respond(tp, mtod(m, caddr_t), th, (tcp_seq)0, th->th_ack,
		    TH_RST, m->m_pkthdr.ph_rtableid);
	} else {
		if (tiflags & TH_SYN)
			tlen++;
		tcp_respond(tp, mtod(m, caddr_t), th, th->th_seq + tlen,
		    (tcp_seq)0, TH_RST|TH_ACK, m->m_pkthdr.ph_rtableid);
	}
	m_freem(m);
	return IPPROTO_DONE;

drop:


	if (otp)
		tcp_trace(TA_DROP, ostate, tp, otp, saveti, 0, tlen);

	m_freem(m);
	return IPPROTO_DONE;
}
