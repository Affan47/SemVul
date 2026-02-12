clock_select(void)
{
	struct peer *peer;
	int	i, j, k, n;
	int	nlist, nl2;
	int	allow;
	int	speer;
	double	d, e, f, g;
	double	high, low;
	double	speermet;
	double	orphmet = 2.0 * U_INT32_MAX;
	struct endpoint endp;
	struct peer *osys_peer;
	struct peer *sys_prefer = NULL;
	struct peer *typesystem = NULL;
	struct peer *typeorphan = NULL;
#ifdef REFCLOCK
	struct peer *typeacts = NULL;
	struct peer *typelocal = NULL;
	struct peer *typepps = NULL;
#endif
	static struct endpoint *endpoint = NULL;
	static int *indx = NULL;
	static peer_select *peers = NULL;
	static u_int endpoint_size = 0;
	static u_int peers_size = 0;
	static u_int indx_size = 0;
	size_t octets;


	osys_peer = sys_peer;
	sys_survivors = 0;
#ifdef LOCKCLOCK
	set_sys_leap(LEAP_NOTINSYNC);
	sys_stratum = STRATUM_UNSPEC;
	memcpy(&sys_refid, "DOWN", 4);
#endif


	nlist = 1;
	for (peer = peer_list; peer != NULL; peer = peer->p_link)
		nlist++;
	endpoint_size = ALIGNED_SIZE(nlist * 2 * sizeof(*endpoint));
	peers_size = ALIGNED_SIZE(nlist * sizeof(*peers));
	indx_size = ALIGNED_SIZE(nlist * 2 * sizeof(*indx));
	octets = endpoint_size + peers_size + indx_size;
	endpoint = erealloc(endpoint, octets);
	peers = INC_ALIGNED_PTR(endpoint, endpoint_size);
	indx = INC_ALIGNED_PTR(peers, peers_size);


	nlist = nl2 = 0;
	for (peer = peer_list; peer != NULL; peer = peer->p_link) {
		peer->new_status = CTL_PST_SEL_REJECT;


		if (peer_unfit(peer))
			continue;


		if (peer->stratum == sys_orphan) {
			u_int32	localmet;
			u_int32 peermet;

			if (peer->dstadr != NULL)
				localmet = ntohl(peer->dstadr->addr_refid);
			else
				localmet = U_INT32_MAX;
			peermet = ntohl(addr2refid(&peer->srcadr));
			if (peermet < localmet && peermet < orphmet) {
				typeorphan = peer;
				orphmet = peermet;
			}
			continue;
		}


		if (peer->stratum > sys_orphan)
			continue;
#ifdef REFCLOCK


		if (!(peer->flags & FLAG_PREFER)) {
			switch (peer->refclktype) {
			case REFCLK_LOCALCLOCK:
				if (current_time > orphwait &&
				    typelocal == NULL)
					typelocal = peer;
				continue;

			case REFCLK_ACTS:
				if (current_time > orphwait &&
				    typeacts == NULL)
					typeacts = peer;
				continue;
			}
		}
#endif


		peer->new_status = CTL_PST_SEL_SANE;
		f = root_distance(peer);
		peers[nlist].peer = peer;
		peers[nlist].error = peer->jitter;
		peers[nlist].synch = f;
		nlist++;


		e = peer->offset;
		endpoint[nl2].type = -1;
		endpoint[nl2].val = e - f;
		nl2++;
		endpoint[nl2].type = 1;
		endpoint[nl2].val = e + f;
		nl2++;
	}


	for (i = 0; i < nl2; i++)
		indx[i] = i;
	for (i = 0; i < nl2; i++) {
		endp = endpoint[indx[i]];
		e = endp.val;
		k = i;
		for (j = i + 1; j < nl2; j++) {
			endp = endpoint[indx[j]];
			if (endp.val < e) {
				e = endp.val;
				k = j;
			}
		}
		if (k != i) {
			j = indx[k];
			indx[k] = indx[i];
			indx[i] = j;
		}
	}
	for (i = 0; i < nl2; i++)
		DPRINTF(3, ("select: endpoint %2d %.6f\n",
			endpoint[indx[i]].type, endpoint[indx[i]].val));


	low = 1e9;
	high = -1e9;
	for (allow = 0; 2 * allow < nlist; allow++) {


		n = 0;
		for (i = 0; i < nl2; i++) {
			low = endpoint[indx[i]].val;
			n -= endpoint[indx[i]].type;
			if (n >= nlist - allow)
				break;
		}
		n = 0;
		for (j = nl2 - 1; j >= 0; j--) {
			high = endpoint[indx[j]].val;
			n += endpoint[indx[j]].type;
			if (n >= nlist - allow)
				break;
		}


		if (high > low)
			break;
	}


	j = 0;
	for (i = 0; i < nlist; i++) {
		double	h;

		peer = peers[i].peer;
		h = peers[i].synch;
		if ((high <= low || peer->offset + h < low ||
		    peer->offset - h > high) && !(peer->flags & FLAG_TRUE))
			continue;

#ifdef REFCLOCK


		if (peer->flags & FLAG_PPS) {
			if (typepps == NULL)
				typepps = peer;
			if (!(peer->flags & FLAG_TSTAMP_PPS))
				continue;
		}
#endif

		if (j != i)
			peers[j] = peers[i];
		j++;
	}
	nlist = j;


	if (nlist == 0) {
		peers[0].error = 0;
		peers[0].synch = sys_mindisp;
#ifdef REFCLOCK
		if (typeacts != NULL) {
			peers[0].peer = typeacts;
			nlist = 1;
		} else if (typelocal != NULL) {
			peers[0].peer = typelocal;
			nlist = 1;
		} else
#endif
		if (typeorphan != NULL) {
			peers[0].peer = typeorphan;
			nlist = 1;
		}
	}


	for (i = 0; i < nlist; i++) {
		peers[i].peer->new_status = CTL_PST_SEL_SELCAND;
		DPRINTF(2, ("select: survivor %s %f\n",
			stoa(&peers[i].peer->srcadr), peers[i].synch));
	}


	while (1) {
		d = 1e9;
		e = -1e9;
		g = 0;
		k = 0;
		for (i = 0; i < nlist; i++) {
			if (peers[i].error < d)
				d = peers[i].error;
			peers[i].seljit = 0;
			if (nlist > 1) {
				f = 0;
				for (j = 0; j < nlist; j++)
					f += DIFF(peers[j].peer->offset,
					    peers[i].peer->offset);
				peers[i].seljit = SQRT(f / (nlist - 1));
			}
			if (peers[i].seljit * peers[i].synch > e) {
				g = peers[i].seljit;
				e = peers[i].seljit * peers[i].synch;
				k = i;
			}
		}
		g = max(g, LOGTOD(sys_precision));
		if (nlist <= max(1, sys_minclock) || g <= d ||
		    ((FLAG_TRUE | FLAG_PREFER) & peers[k].peer->flags))
			break;

		DPRINTF(3, ("select: drop %s seljit %.6f jit %.6f\n",
			ntoa(&peers[k].peer->srcadr), g, d));
		if (nlist > sys_maxclock)
			peers[k].peer->new_status = CTL_PST_SEL_EXCESS;
		for (j = k + 1; j < nlist; j++)
			peers[j - 1] = peers[j];
		nlist--;
	}


	e = 1e9;
	speer = 0;
	leap_vote_ins = 0;
	leap_vote_del = 0;
	for (i = 0; i < nlist; i++) {
		peer = peers[i].peer;
		peer->unreach = 0;
		peer->new_status = CTL_PST_SEL_SYNCCAND;
		sys_survivors++;
		if (peer->leap == LEAP_ADDSECOND) {
			if (peer->flags & FLAG_REFCLOCK)
				leap_vote_ins = nlist;
			else if (leap_vote_ins < nlist)
				leap_vote_ins++;
		}
		if (peer->leap == LEAP_DELSECOND) {
			if (peer->flags & FLAG_REFCLOCK)
				leap_vote_del = nlist;
			else if (leap_vote_del < nlist)
				leap_vote_del++;
		}
		if (peer->flags & FLAG_PREFER)
			sys_prefer = peer;
		speermet = peers[i].seljit * peers[i].synch +
		    peer->stratum * sys_mindisp;
		if (speermet < e) {
			e = speermet;
			speer = i;
		}
	}


	if (nlist > 0 && nlist >= sys_minsane) {
		double	x;

		typesystem = peers[speer].peer;
		if (osys_peer == NULL || osys_peer == typesystem) {
			sys_clockhop = 0;
		} else if ((x = fabs(typesystem->offset -
		    osys_peer->offset)) < sys_mindisp) {
			if (sys_clockhop == 0)
				sys_clockhop = sys_mindisp;
			else
				sys_clockhop *= .5;
			DPRINTF(1, ("select: clockhop %d %.6f %.6f\n",
				j, x, sys_clockhop));
			if (fabs(x) < sys_clockhop)
				typesystem = osys_peer;
			else
				sys_clockhop = 0;
		} else {
			sys_clockhop = 0;
		}
	}


	if (typesystem != NULL) {
		if (sys_prefer == NULL) {
			typesystem->new_status = CTL_PST_SEL_SYSPEER;
			clock_combine(peers, sys_survivors, speer);
		} else {
			typesystem = sys_prefer;
			sys_clockhop = 0;
			typesystem->new_status = CTL_PST_SEL_SYSPEER;
			sys_offset = typesystem->offset;
			sys_jitter = typesystem->jitter;
		}
		DPRINTF(1, ("select: combine offset %.9f jitter %.9f\n",
			sys_offset, sys_jitter));
	}
#ifdef REFCLOCK


	if (typepps != NULL && fabs(sys_offset) < 0.4 &&
	    (typepps->refclktype != REFCLK_ATOM_PPS ||
	    (typepps->refclktype == REFCLK_ATOM_PPS && (sys_prefer !=
	    NULL || (typesystem == NULL && sys_minsane == 0))))) {
		typesystem = typepps;
		sys_clockhop = 0;
		typesystem->new_status = CTL_PST_SEL_PPS;
 		sys_offset = typesystem->offset;
		sys_jitter = typesystem->jitter;
		DPRINTF(1, ("select: pps offset %.9f jitter %.9f\n",
			sys_offset, sys_jitter));
	}
#endif


	if (typesystem == NULL) {
		if (osys_peer != NULL) {
			if (sys_orphwait > 0)
				orphwait = current_time + sys_orphwait;
			report_event(EVNT_NOPEER, NULL, NULL);
		}
		sys_peer = NULL;
		for (peer = peer_list; peer != NULL; peer = peer->p_link)
			peer->status = peer->new_status;
		return;
	}


	if (typesystem->epoch <= sys_epoch)
		return;


	if (osys_peer != typesystem)
		report_event(PEVNT_NEWPEER, typesystem, NULL);
	for (peer = peer_list; peer != NULL; peer = peer->p_link)
		peer->status = peer->new_status;
	clock_update(typesystem);
}
