poll_update(
	struct peer *peer,
	u_char	mpoll
	)
{
	u_long	next, utemp;
	u_char	hpoll;


	hpoll = max(min(peer->maxpoll, mpoll), peer->minpoll);

#ifdef AUTOKEY


	if ((peer->flags & FLAG_SKEY) && hpoll != peer->hpoll)
		key_expire(peer);
#endif
	peer->hpoll = hpoll;


	utemp = current_time + max(peer->throttle - (NTP_SHIFT - 1) *
	    (1 << peer->minpoll), ntp_minpkt);
	if (peer->burst > 0) {
		if (peer->nextdate > current_time)
			return;
#ifdef REFCLOCK
		else if (peer->flags & FLAG_REFCLOCK)
			peer->nextdate = current_time + RESP_DELAY;
#endif
		else
			peer->nextdate = utemp;

#ifdef AUTOKEY


	} else if (peer->cmmd != NULL) {
		if (peer->nextdate > current_time) {
			if (peer->nextdate + ntp_minpkt != utemp)
				peer->nextdate = utemp;
		} else {
			peer->nextdate = utemp;
		}
#endif


	} else {
		if (peer->retry > 0)
			hpoll = peer->minpoll;
		else if (!(peer->reach))
			hpoll = peer->hpoll;
		else
			hpoll = min(peer->ppoll, peer->hpoll);
#ifdef REFCLOCK
		if (peer->flags & FLAG_REFCLOCK)
			next = 1 << hpoll;
		else
#endif
			next = ((0x1000UL | (ntp_random() & 0x0ff)) <<
			    hpoll) >> 12;
		next += peer->outdate;
		if (next > utemp)
			peer->nextdate = next;
		else
			peer->nextdate = utemp;
		if (peer->throttle > (1 << peer->minpoll))
			peer->nextdate += ntp_minpkt;
	}
	DPRINTF(2, ("poll_update: at %lu %s poll %d burst %d retry %d head %d early %lu next %lu\n",
		    current_time, ntoa(&peer->srcadr), peer->hpoll,
		    peer->burst, peer->retry, peer->throttle,
		    utemp - current_time, peer->nextdate -
		    current_time));
}
