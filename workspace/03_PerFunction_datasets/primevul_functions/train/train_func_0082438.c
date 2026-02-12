receive(
	struct recvbuf *rbufp
	)
{
	register struct peer *peer;
	register struct pkt *pkt;
	u_char	hisversion;
	u_char	hisleap;
	u_char	hismode;
	u_char	hisstratum;
	u_short	restrict_mask;
	int	has_mac;
	int	authlen;
	int	is_authentic = 0;
	int	retcode = AM_NOMATCH;
	keyid_t	skeyid = 0;
	u_int32	opcode = 0;
	sockaddr_u *dstadr_sin;
	struct peer *peer2;
	endpt *	match_ep;
	l_fp	p_org;
	l_fp	p_rec;
	l_fp	p_xmt;
#ifdef AUTOKEY
	char	hostname[NTP_MAXSTRLEN + 1];
	char	*groupname = NULL;
	struct autokey *ap;
	int	rval;
	keyid_t	pkeyid = 0, tkeyid = 0;
#endif
#ifdef HAVE_NTP_SIGND
	static unsigned char zero_key[16];
#endif


	sys_received++;
	if (0 == SRCPORT(&rbufp->recv_srcadr)) {
		sys_badlength++;
		return;
	}
	restrict_mask = restrictions(&rbufp->recv_srcadr);
	DPRINTF(2, ("receive: at %ld %s<-%s flags %x restrict %03x\n",
		    current_time, stoa(&rbufp->dstadr->sin),
		    stoa(&rbufp->recv_srcadr),
		    rbufp->dstadr->flags, restrict_mask));
	pkt = &rbufp->recv_pkt;
	hisversion = PKT_VERSION(pkt->li_vn_mode);
	hisleap = PKT_LEAP(pkt->li_vn_mode);
	hismode = (int)PKT_MODE(pkt->li_vn_mode);
	hisstratum = PKT_TO_STRATUM(pkt->stratum);
	if (restrict_mask & RES_IGNORE) {
		sys_restricted++;
		return;
	}
	if (hismode == MODE_PRIVATE) {
		if (!ntp_mode7 || (restrict_mask & RES_NOQUERY)) {
			sys_restricted++;
			return;
		}
		process_private(rbufp, ((restrict_mask &
		    RES_NOMODIFY) == 0));
		return;
	}
	if (hismode == MODE_CONTROL) {
		if (restrict_mask & RES_NOQUERY) {
			sys_restricted++;
			return;
		}
		process_control(rbufp, restrict_mask);
		return;
	}
	if (restrict_mask & RES_DONTSERVE) {
		sys_restricted++;
		return;
	}


	if (restrict_mask & RES_FLAKE) {
		if ((double)ntp_random() / 0x7fffffff < .1) {
			sys_restricted++;
			return;
		}
	}


	if (hisversion == NTP_VERSION) {
		sys_newversion++;
	} else if (!(restrict_mask & RES_VERSION) && hisversion >=
	    NTP_OLDVERSION) {
		sys_oldversion++;
	} else {
		sys_badlength++;
		return;
	}


	if (hismode == MODE_UNSPEC) {
		if (hisversion == NTP_OLDVERSION) {
			hismode = MODE_CLIENT;
		} else {
			sys_badlength++;
			return;
		}
	}


	authlen = LEN_PKT_NOMAC;
	has_mac = rbufp->recv_length - authlen;
	while (has_mac > 0) {
		u_int32	len;
#ifdef AUTOKEY
		u_int32	hostlen;
		struct exten *ep;
#endif

		if (has_mac % 4 != 0 || has_mac < (int)MIN_MAC_LEN) {
			sys_badlength++;
			return;
		}
		if (has_mac <= (int)MAX_MAC_LEN) {
			skeyid = ntohl(((u_int32 *)pkt)[authlen / 4]);
			break;

		} else {
			opcode = ntohl(((u_int32 *)pkt)[authlen / 4]);
			len = opcode & 0xffff;
			if (len % 4 != 0 || len < 4 || (int)len +
			    authlen > rbufp->recv_length) {
				sys_badlength++;
				return;
			}
#ifdef AUTOKEY


			if ((opcode & 0x3fff0000) == CRYPTO_ASSOC &&
			    sys_groupname != NULL) {
				ep = (struct exten *)&((u_int32 *)pkt)[authlen / 4];
				hostlen = ntohl(ep->vallen);
				if (hostlen >= sizeof(hostname) ||
				    hostlen > len -
				    offsetof(struct exten, pkt)) {
					sys_badlength++;
					return;
				}
				memcpy(hostname, &ep->pkt, hostlen);
				hostname[hostlen] = '\0';
				groupname = strchr(hostname, '@');
				if (groupname == NULL) {
					sys_declined++;
					return;
				}
				groupname++;
			}
#endif
			authlen += len;
			has_mac -= len;
		}
	}


	if (has_mac < 0) {
		sys_badlength++;
		return;
	}


	if (restrict_mask & RES_DONTTRUST && has_mac == 0) {
		sys_restricted++;
		return;
	}


	restrict_mask = ntp_monitor(rbufp, restrict_mask);
	if (restrict_mask & RES_LIMITED) {
		sys_limitrejected++;
		if (!(restrict_mask & RES_KOD) || MODE_BROADCAST ==
		    hismode || MODE_SERVER == hismode) {
			if (MODE_SERVER == hismode)
				DPRINTF(1, ("Possibly self-induced rate limiting of MODE_SERVER from %s\n",
					stoa(&rbufp->recv_srcadr)));
			return;
		}
		if (hismode == MODE_CLIENT)
			fast_xmit(rbufp, MODE_SERVER, skeyid,
			    restrict_mask);
		else
			fast_xmit(rbufp, MODE_ACTIVE, skeyid,
			    restrict_mask);
		return;
	}
	restrict_mask &= ~RES_KOD;


	peer = findpeer(rbufp,  hismode, &retcode);
	dstadr_sin = &rbufp->dstadr->sin;
	NTOHL_FP(&pkt->org, &p_org);
	NTOHL_FP(&pkt->rec, &p_rec);
	NTOHL_FP(&pkt->xmt, &p_xmt);


	if (has_mac == 0) {
		restrict_mask &= ~RES_MSSNTP;
		is_authentic = AUTH_NONE;
#ifdef DEBUG
		if (debug)
			printf(
			    "receive: at %ld %s<-%s mode %d len %d\n",
			    current_time, stoa(dstadr_sin),
			    stoa(&rbufp->recv_srcadr), hismode,
			    authlen);
#endif
	} else if (has_mac == 4) {
		restrict_mask &= ~RES_MSSNTP;
		is_authentic = AUTH_CRYPTO;
#ifdef DEBUG
		if (debug)
			printf(
			    "receive: at %ld %s<-%s mode %d keyid %08x len %d auth %d\n",
			    current_time, stoa(dstadr_sin),
			    stoa(&rbufp->recv_srcadr), hismode, skeyid,
			    authlen + has_mac, is_authentic);
#endif

#ifdef HAVE_NTP_SIGND


	} else if (has_mac == MAX_MD5_LEN && (restrict_mask & RES_MSSNTP) &&
	   (retcode == AM_FXMIT || retcode == AM_NEWPASS) &&
	   (memcmp(zero_key, (char *)pkt + authlen + 4, MAX_MD5_LEN - 4) ==
	   0)) {
		is_authentic = AUTH_NONE;
#endif

	} else {
		restrict_mask &= ~RES_MSSNTP;
#ifdef AUTOKEY


		if (crypto_flags && skeyid > NTP_MAXKEY) {


			if (has_mac < (int)MAX_MD5_LEN) {
				sys_badauth++;
				return;
			}
			if (hismode == MODE_BROADCAST) {


				if (crypto_flags && rbufp->dstadr ==
				    ANY_INTERFACE_CHOOSE(&rbufp->recv_srcadr)) {
					sys_restricted++;
					return;
				}
				pkeyid = 0;
				if (!SOCK_UNSPEC(&rbufp->dstadr->bcast))
					dstadr_sin =
					    &rbufp->dstadr->bcast;
			} else if (peer == NULL) {
				pkeyid = session_key(
				    &rbufp->recv_srcadr, dstadr_sin, 0,
				    sys_private, 0);
			} else {
				pkeyid = peer->pcookie;
			}


			if (authlen > (int)LEN_PKT_NOMAC && pkeyid != 0) {
				session_key(&rbufp->recv_srcadr,
				    dstadr_sin, skeyid, 0, 2);
				tkeyid = session_key(
				    &rbufp->recv_srcadr, dstadr_sin,
				    skeyid, pkeyid, 0);
			} else {
				tkeyid = session_key(
				    &rbufp->recv_srcadr, dstadr_sin,
				    skeyid, pkeyid, 2);
			}

		}
#endif


		if (!authdecrypt(skeyid, (u_int32 *)pkt, authlen,
		    has_mac))
			is_authentic = AUTH_ERROR;
		else
			is_authentic = AUTH_OK;
#ifdef AUTOKEY
		if (crypto_flags && skeyid > NTP_MAXKEY)
			authtrust(skeyid, 0);
#endif
#ifdef DEBUG
		if (debug)
			printf(
			    "receive: at %ld %s<-%s mode %d keyid %08x len %d auth %d\n",
			    current_time, stoa(dstadr_sin),
			    stoa(&rbufp->recv_srcadr), hismode, skeyid,
			    authlen + has_mac, is_authentic);
#endif
	}


	switch (retcode) {


	case AM_FXMIT:


		if (!(rbufp->dstadr->flags & INT_MCASTOPEN)) {
			if (AUTH(restrict_mask & RES_DONTTRUST,
			   is_authentic)) {
				fast_xmit(rbufp, MODE_SERVER, skeyid,
				    restrict_mask);
			} else if (is_authentic == AUTH_ERROR) {
				fast_xmit(rbufp, MODE_SERVER, 0,
				    restrict_mask);
				sys_badauth++;
			} else {
				sys_restricted++;
			}
			return;
		}


		if (!sys_manycastserver) {
			sys_restricted++;
			return;
		}

#ifdef AUTOKEY


		if (group_test(groupname, NULL)) {
			sys_declined++;
			return;
		}
#endif


		if (sys_leap == LEAP_NOTINSYNC || sys_stratum >=
		    hisstratum || (!sys_cohort && sys_stratum ==
		    hisstratum + 1) || rbufp->dstadr->addr_refid ==
		    pkt->refid) {
			sys_declined++;
			return;
		}


		if (AUTH(restrict_mask & RES_DONTTRUST, is_authentic))
			fast_xmit(rbufp, MODE_SERVER, skeyid,
			    restrict_mask);
		return;


	case AM_MANYCAST:

#ifdef AUTOKEY


		if (group_test(groupname, NULL)) {
			sys_declined++;
			return;
		}
#endif
		if ((peer2 = findmanycastpeer(rbufp)) == NULL) {
			sys_restricted++;
			return;
		}
		if (!AUTH((!(peer2->cast_flags & MDF_POOL) &&
		    sys_authenticate) | (restrict_mask & (RES_NOPEER |
		    RES_DONTTRUST)), is_authentic)) {
			sys_restricted++;
			return;
		}


		if (hisleap == LEAP_NOTINSYNC || hisstratum <
		    sys_floor || hisstratum >= sys_ceiling) {
			sys_declined++;
			return;
		}
		peer = newpeer(&rbufp->recv_srcadr, NULL, rbufp->dstadr,
			       MODE_CLIENT, hisversion, peer2->minpoll,
			       peer2->maxpoll, FLAG_PREEMPT |
			       (FLAG_IBURST & peer2->flags), MDF_UCAST |
			       MDF_UCLNT, 0, skeyid, sys_ident);
		if (NULL == peer) {
			sys_declined++;
			return;
		}


		if (peer2->cast_flags & MDF_POOL)
			peer2->nextdate = current_time + 1;


		return;


	case AM_NEWBCL:

#ifdef AUTOKEY


		if (group_test(groupname, sys_ident)) {
			sys_declined++;
			return;
		}
#endif
		if (sys_bclient == 0) {
			sys_restricted++;
			return;
		}
		if (!AUTH(sys_authenticate | (restrict_mask &
		    (RES_NOPEER | RES_DONTTRUST)), is_authentic)) {
			sys_restricted++;
			return;
		}


		if (hisleap == LEAP_NOTINSYNC || hisstratum <
		    sys_floor || hisstratum >= sys_ceiling) {
			sys_declined++;
			return;
		}

#ifdef AUTOKEY


		if (crypto_flags && skeyid > NTP_MAXKEY && (opcode &
		    0xffff0000) != (CRYPTO_ASSOC | CRYPTO_RESP)) {
			sys_declined++;
			return;
		}
#endif


		if (!(INT_MCASTOPEN & rbufp->dstadr->flags))
			match_ep = rbufp->dstadr;
		else
			match_ep = NULL;


		if (sys_bdelay != 0) {
#ifdef AUTOKEY


			if (crypto_flags && skeyid > NTP_MAXKEY) {
				sys_restricted++;
				return;
			}
#endif


			peer = newpeer(&rbufp->recv_srcadr, NULL,
			    match_ep, MODE_BCLIENT, hisversion,
			    pkt->ppoll, pkt->ppoll, FLAG_PREEMPT,
			    MDF_BCLNT, 0, skeyid, sys_ident);
			if (NULL == peer) {
				sys_restricted++;
				return;

			} else {
				peer->delay = sys_bdelay;
			}
			break;
		}


		peer = newpeer(&rbufp->recv_srcadr, NULL, match_ep,
		    MODE_CLIENT, hisversion, pkt->ppoll, pkt->ppoll,
		    FLAG_BC_VOL | FLAG_IBURST | FLAG_PREEMPT, MDF_BCLNT,
		    0, skeyid, sys_ident);
		if (NULL == peer) {
			sys_restricted++;
			return;
		}
#ifdef AUTOKEY
		if (skeyid > NTP_MAXKEY)
			crypto_recv(peer, rbufp);
#endif

		return;


	case AM_NEWPASS:

#ifdef AUTOKEY


		if (group_test(groupname, sys_ident)) {
			sys_declined++;
			return;
		}
#endif
		if (!AUTH(sys_authenticate | (restrict_mask &
		    (RES_NOPEER | RES_DONTTRUST)), is_authentic)) {


			if (AUTH(restrict_mask & RES_DONTTRUST,
			    is_authentic)) {
				fast_xmit(rbufp, MODE_PASSIVE, skeyid,
				    restrict_mask);
				return;
			}
			if (is_authentic == AUTH_ERROR) {
				fast_xmit(rbufp, MODE_ACTIVE, 0,
				    restrict_mask);
				sys_restricted++;
				return;
			}
		}


		if (hisleap != LEAP_NOTINSYNC && (hisstratum <
		    sys_floor || hisstratum >= sys_ceiling)) {
			sys_declined++;
			return;
		}


		if ((peer = newpeer(&rbufp->recv_srcadr, NULL,
		    rbufp->dstadr, MODE_PASSIVE, hisversion, pkt->ppoll,
		    NTP_MAXDPOLL, 0, MDF_UCAST, 0, skeyid,
		    sys_ident)) == NULL) {
			sys_declined++;
			return;
		}
		break;


	case AM_PROCPKT:

#ifdef AUTOKEY


		if (group_test(groupname, peer->ident)) {
			sys_declined++;
			return;
		}
#endif
		break;


	case AM_ERR:
		sys_declined++;
		return;


	default:
		sys_declined++;
		return;
	}

#ifdef AUTOKEY


	if (is_authentic != AUTH_CRYPTO && (((peer->flags &
	    FLAG_SKEY) && skeyid <= NTP_MAXKEY) || (!(peer->flags &
	    FLAG_SKEY) && skeyid > NTP_MAXKEY))) {
		sys_badauth++;
		return;
	}
#endif
	peer->received++;
	peer->flash &= ~PKT_TEST_MASK;
	if (peer->flags & FLAG_XBOGUS) {
		peer->flags &= ~FLAG_XBOGUS;
		peer->flash |= TEST3;
	}


	if (L_ISZERO(&p_xmt)) {
		peer->flash |= TEST3;


	} else if (L_ISEQU(&peer->xmt, &p_xmt)) {
		peer->flash |= TEST1;
		peer->oldpkt++;
		return;


	} else if (hismode == MODE_BROADCAST) {
		if (!L_ISZERO(&p_org) && !(peer->flags & FLAG_XB)) {
			peer->flags |= FLAG_XB;
			peer->aorg = p_xmt;
			peer->borg = rbufp->recv_time;
			report_event(PEVNT_XLEAVE, peer, NULL);
			return;
		}


	} else if (peer->flip == 0) {
		if (!L_ISEQU(&p_org, &peer->aorg)) {
			peer->bogusorg++;
			peer->flash |= TEST2;
			if (!L_ISZERO(&peer->dst) && L_ISEQU(&p_org,
			    &peer->dst)) {
				peer->flip = 1;
				report_event(PEVNT_XLEAVE, peer, NULL);
			}
		} else {
			L_CLR(&peer->aorg);
		}


	} else if (L_ISZERO(&p_org) || L_ISZERO(&p_rec) ||
	    L_ISZERO(&peer->dst)) {
		peer->flash |= TEST3;


	} else if (!L_ISZERO(&peer->dst) && !L_ISEQU(&p_org,
	    &peer->dst)) {
		peer->bogusorg++;
		peer->flags |= FLAG_XBOGUS;
		peer->flash |= TEST2;
	}


	if (is_authentic == AUTH_CRYPTO) {
		report_event(PEVNT_AUTH, peer, "crypto_NAK");
		peer->flash |= TEST5;
		peer->badauth++;
		if (peer->flags & FLAG_PREEMPT) {
			unpeer(peer);
			return;
		}
#ifdef AUTOKEY
		if (peer->crypto)
			peer_clear(peer, "AUTH");
#endif
		return;


	} else if (!AUTH(peer->keyid || has_mac ||
			 (restrict_mask & RES_DONTTRUST), is_authentic)) {
		report_event(PEVNT_AUTH, peer, "digest");
		peer->flash |= TEST5;
		peer->badauth++;
		if (has_mac &&
		    (hismode == MODE_ACTIVE || hismode == MODE_PASSIVE))
			fast_xmit(rbufp, MODE_ACTIVE, 0, restrict_mask);
		if (peer->flags & FLAG_PREEMPT) {
			unpeer(peer);
			return;
		}
#ifdef AUTOKEY
		if (peer->crypto)
			peer_clear(peer, "AUTH");
#endif
		return;
	}


	if (peer->flip == 0) {
		if (hismode != MODE_BROADCAST)
			peer->rec = p_xmt;
		peer->dst = rbufp->recv_time;
	}
	peer->xmt = p_xmt;


	peer->ppoll = max(peer->minpoll, pkt->ppoll);
	if (hismode == MODE_SERVER && hisleap == LEAP_NOTINSYNC &&
	    hisstratum == STRATUM_UNSPEC && memcmp(&pkt->refid,
	    "RATE", 4) == 0) {
		peer->selbroken++;
		report_event(PEVNT_RATE, peer, NULL);
		if (pkt->ppoll > peer->minpoll)
			peer->minpoll = peer->ppoll;
		peer->burst = peer->retry = 0;
		peer->throttle = (NTP_SHIFT + 1) * (1 << peer->minpoll);
		poll_update(peer, pkt->ppoll);
		return;
	}


	peer->timereceived = current_time;
	if (is_authentic == AUTH_OK)
		peer->flags |= FLAG_AUTHENTIC;
	else
		peer->flags &= ~FLAG_AUTHENTIC;

#ifdef AUTOKEY


	if (peer->flags & FLAG_SKEY) {


		ap = (struct autokey *)peer->recval.ptr;
		if (ap != NULL) {
			if (ap->seq > 0)
				ap->seq--;
		}
		peer->flash |= TEST8;
		rval = crypto_recv(peer, rbufp);
		if (rval == XEVNT_OK) {
			peer->unreach = 0;
		} else {
			if (rval == XEVNT_ERR) {
				report_event(PEVNT_RESTART, peer,
				    "crypto error");
				peer_clear(peer, "CRYP");
				peer->flash |= TEST9;
				if (peer->flags & FLAG_PREEMPT)
					unpeer(peer);
			}
			return;
		}


		if (hismode == MODE_SERVER) {
			if (skeyid == peer->keyid)
				peer->flash &= ~TEST8;


		} else if (!(peer->flash & TEST8)) {
			peer->pkeyid = skeyid;


		} else if (ap != NULL) {
			int i;

			for (i = 0; ; i++) {
				if (tkeyid == peer->pkeyid ||
				    tkeyid == ap->key) {
					peer->flash &= ~TEST8;
					peer->pkeyid = skeyid;
					ap->seq -= i;
					break;
				}
				if (i > ap->seq) {
					peer->crypto &=
					    ~CRYPTO_FLAG_AUTO;
					break;
				}
				tkeyid = session_key(
				    &rbufp->recv_srcadr, dstadr_sin,
				    tkeyid, pkeyid, 0);
			}
			if (peer->flash & TEST8)
				report_event(PEVNT_AUTH, peer, "keylist");
		}
		if (!(peer->crypto & CRYPTO_FLAG_PROV))
			peer->flash |= TEST8;


		if (current_time > peer->refresh) {
			report_event(PEVNT_RESTART, peer,
			    "crypto refresh");
			peer_clear(peer, "TIME");
			return;
		}
	}
#endif


	process_packet(peer, pkt, rbufp->recv_length);


	if (peer->flip != 0) {
		peer->rec = p_rec;
		peer->dst = rbufp->recv_time;
		if (peer->nextdate - current_time < (1U << min(peer->ppoll,
		    peer->hpoll)) / 2)
			peer->nextdate++;
		else
			peer->nextdate--;
	}
}
