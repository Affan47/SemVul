transmit(
	struct peer *peer
	)
{
	u_char	hpoll;


	hpoll = peer->hpoll;


	if (peer->cast_flags & (MDF_BCAST | MDF_MCAST)) {
		peer->outdate = current_time;
		if (sys_leap != LEAP_NOTINSYNC)
			peer_xmit(peer);
		poll_update(peer, hpoll);
		return;
	}


	if (peer->cast_flags & MDF_ACAST) {
		peer->outdate = current_time;
		if (peer->unreach > sys_beacon) {
			peer->unreach = 0;
			peer->ttl = 0;
			peer_xmit(peer);
		} else if (sys_survivors < sys_minclock ||
		    peer_associations < sys_maxclock) {
			if (peer->ttl < (u_int32)sys_ttlmax)
				peer->ttl++;
			peer_xmit(peer);
		}
		peer->unreach++;
		poll_update(peer, hpoll);
		return;
	}


	if (peer->cast_flags & MDF_POOL) {
		peer->outdate = current_time;
		if ((peer_associations <= 2 * sys_maxclock) &&
		    (peer_associations < sys_maxclock ||
		     sys_survivors < sys_minclock))
			pool_xmit(peer);
		poll_update(peer, hpoll);
		return;
	}


	if (peer->burst == 0) {
		u_char oreach;


		oreach = peer->reach;
		peer->outdate = current_time;
		peer->unreach++;
		peer->reach <<= 1;
		if (!peer->reach) {


			clock_filter(peer, 0., 0., MAXDISPERSE);
			if (oreach) {
				peer_unfit(peer);
				report_event(PEVNT_UNREACH, peer, NULL);
			}
			if ((peer->flags & FLAG_IBURST) &&
			    peer->retry == 0)
				peer->retry = NTP_RETRY;
		} else {


			hpoll = sys_poll;
			if (!(peer->flags & FLAG_PREEMPT))
				peer->unreach = 0;
			if ((peer->flags & FLAG_BURST) && peer->retry ==
			    0 && !peer_unfit(peer))
				peer->retry = NTP_RETRY;
		}


		if (peer->unreach >= NTP_UNREACH) {
			hpoll++;

			if (!(peer->flags & (FLAG_CONFIG | FLAG_PREEMPT))) {
				report_event(PEVNT_RESTART, peer, "timeout");
				peer_clear(peer, "TIME");
				unpeer(peer);
				return;
			}
			if ((peer->flags & FLAG_PREEMPT) &&
			    (peer_associations > sys_maxclock) &&
			    score_all(peer)) {
				report_event(PEVNT_RESTART, peer, "timeout");
				peer_clear(peer, "TIME");
				unpeer(peer);
				return;
			}
		}
	} else {
		peer->burst--;
		if (peer->burst == 0) {


			if (mode_ntpdate) {
				peer_ntpdate--;
				if (peer_ntpdate == 0) {
					msyslog(LOG_NOTICE,
					    "ntpd: no servers found");
					if (!msyslog_term)
						printf(
						    "ntpd: no servers found\n");
					exit (0);
				}
			}
		}
	}
	if (peer->retry > 0)
		peer->retry--;


	if (peer->hmode != MODE_BCLIENT)
		peer_xmit(peer);
	poll_update(peer, hpoll);
}
