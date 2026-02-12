process_packet(
	register struct peer *peer,
	register struct pkt *pkt,
	u_int	len
	)
{
	double	t34, t21;
	double	p_offset, p_del, p_disp;
	l_fp	p_rec, p_xmt, p_org, p_reftime, ci;
	u_char	pmode, pleap, pversion, pstratum;
	char	statstr[NTP_MAXSTRLEN];
#ifdef ASSYM
	int	itemp;
	double	etemp, ftemp, td;
#endif

	sys_processed++;
	peer->processed++;
	p_del = FPTOD(NTOHS_FP(pkt->rootdelay));
#ifdef __GNUC__
	p_offset = 0;
#endif
	p_disp = FPTOD(NTOHS_FP(pkt->rootdisp));
	NTOHL_FP(&pkt->reftime, &p_reftime);
	NTOHL_FP(&pkt->org, &p_org);
	NTOHL_FP(&pkt->rec, &p_rec);
	NTOHL_FP(&pkt->xmt, &p_xmt);
	pmode = PKT_MODE(pkt->li_vn_mode);
	pleap = PKT_LEAP(pkt->li_vn_mode);
	pversion = PKT_VERSION(pkt->li_vn_mode);
	pstratum = PKT_TO_STRATUM(pkt->stratum);


	record_raw_stats(&peer->srcadr, peer->dstadr ?
	    &peer->dstadr->sin : NULL,
	    &p_org, &p_rec, &p_xmt, &peer->dst,
	    pleap, pversion, pmode, pstratum, pkt->ppoll, pkt->precision,
	    p_del, p_disp, pkt->refid);
	peer->leap = pleap;
	peer->stratum = min(pstratum, STRATUM_UNSPEC);
	peer->pmode = pmode;
	peer->precision = pkt->precision;
	peer->rootdelay = p_del;
	peer->rootdisp = p_disp;
	peer->refid = pkt->refid;
	peer->reftime = p_reftime;


	if (peer->retry > 0) {
		peer->retry = 0;
		if (peer->reach)
			peer->burst = min(1 << (peer->hpoll -
			    peer->minpoll), NTP_SHIFT) - 1;
		else
			peer->burst = NTP_IBURST - 1;
		if (peer->burst > 0)
			peer->nextdate = current_time;
	}
	poll_update(peer, peer->hpoll);


	if (pleap == LEAP_NOTINSYNC ||
	    pstratum < sys_floor || pstratum >= sys_ceiling)
		peer->flash |= TEST6;
	if (p_del / 2 + p_disp >= MAXDISPERSE)
		peer->flash |= TEST7;


	if (peer->flash & PKT_TEST_MASK) {
		peer->seldisptoolarge++;
#ifdef DEBUG
		if (debug)
			printf("packet: flash header %04x\n",
			    peer->flash);
#endif
		return;
	}


	if (!peer->reach) {
		report_event(PEVNT_REACH, peer, NULL);
		peer->timereachable = current_time;
	}
	peer->reach |= 1;


	if (peer->flip != 0) {
		ci = p_xmt;
		L_SUB(&ci, &peer->dst);
		LFPTOD(&ci, t34);
		ci = p_rec;
		if (peer->flip > 0)
			L_SUB(&ci, &peer->borg);
		else
			L_SUB(&ci, &peer->aorg);
		LFPTOD(&ci, t21);
		p_del = t21 - t34;
		p_offset = (t21 + t34) / 2.;
		if (p_del < 0 || p_del > 1.) {
			snprintf(statstr, sizeof(statstr),
			    "t21 %.6f t34 %.6f", t21, t34);
			report_event(PEVNT_XERR, peer, statstr);
			return;
		}


	} else if (peer->pmode == MODE_BROADCAST) {


		if (peer->flags & FLAG_XB) {
			ci = p_org;
			L_SUB(&ci, &peer->aorg);
			LFPTOD(&ci, t34);
			ci = p_org;
			L_SUB(&ci, &peer->borg);
			LFPTOD(&ci, t21);
			peer->aorg = p_xmt;
			peer->borg = peer->dst;
			if (t34 < 0 || t34 > 1.) {
				snprintf(statstr, sizeof(statstr),
				    "offset %.6f delay %.6f", t21, t34);
				report_event(PEVNT_XERR, peer, statstr);
				return;
			}
			p_offset = t21;
			peer->xleave = t34;


		} else {
			ci = p_xmt;
			L_SUB(&ci, &peer->dst);
			LFPTOD(&ci, t34);
			p_offset = t34;
		}


		if (FLAG_BC_VOL & peer->flags) {
			peer->flags &= ~FLAG_BC_VOL;
			peer->delay = fabs(peer->offset - p_offset) * 2;
		}
		p_del = peer->delay;
		p_offset += p_del / 2;


	} else {
		ci = p_xmt;
		L_SUB(&ci, &peer->dst);
		LFPTOD(&ci, t34);
		ci = p_rec;
		L_SUB(&ci, &p_org);
		LFPTOD(&ci, t21);
		p_del = fabs(t21 - t34);
		p_offset = (t21 + t34) / 2.;
	}
	p_del = max(p_del, LOGTOD(sys_precision));
	p_disp = LOGTOD(sys_precision) + LOGTOD(peer->precision) +
	    clock_phi * p_del;

#if ASSYM


	if (peer->t21_last > 0 && peer->t34_bytes > 0) {
		itemp = peer->t21_bytes - peer->t21_last;
		if (itemp > 25) {
			etemp = t21 - peer->t21;
			if (fabs(etemp) > 1e-6) {
				ftemp = itemp / etemp;
				if (ftemp > 1000.)
					peer->r21 = ftemp;
			}
		}
		itemp = len - peer->t34_bytes;
		if (itemp > 25) {
			etemp = -t34 - peer->t34;
			if (fabs(etemp) > 1e-6) {
				ftemp = itemp / etemp;
				if (ftemp > 1000.)
					peer->r34 = ftemp;
			}
		}
	}


 	peer->t21 = t21;
	peer->t21_last = peer->t21_bytes;
	peer->t34 = -t34;
	peer->t34_bytes = len;
#ifdef DEBUG
	if (debug > 1)
		printf("packet: t21 %.9lf %d t34 %.9lf %d\n", peer->t21,
		    peer->t21_bytes, peer->t34, peer->t34_bytes);
#endif
	if (peer->r21 > 0 && peer->r34 > 0 && p_del > 0) {
		if (peer->pmode != MODE_BROADCAST)
			td = (peer->r34 / (peer->r21 + peer->r34) -
			    .5) * p_del;
		else
			td = 0;


		t21 -= td;
		t34 -= td;
#ifdef DEBUG
		if (debug > 1)
			printf("packet: del %.6lf r21 %.1lf r34 %.1lf %.6lf\n",
			    p_del, peer->r21 / 1e3, peer->r34 / 1e3,
			    td);
#endif
	}
#endif


	clock_filter(peer, p_offset + peer->bias, p_del, p_disp);


	if ((FLAG_BC_VOL & peer->flags) && MODE_CLIENT == peer->hmode &&
	    !(TEST11 & peer_unfit(peer))) {
#ifdef AUTOKEY
		if (peer->flags & FLAG_SKEY) {
			if (!(~peer->crypto & CRYPTO_FLAG_ALL))
				peer->hmode = MODE_BCLIENT;
		} else {
			peer->hmode = MODE_BCLIENT;
		}
#else
		peer->hmode = MODE_BCLIENT;
#endif
	}
}
