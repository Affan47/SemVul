link_established(int linkunit)
{
	int auth;
	lcp_options *wo = &lcp_wantoptions[ lns[linkunit].lcp_unit ];
	lcp_options *go = &lcp_gotoptions[ lns[linkunit].lcp_unit ];
	lcp_options *ho = &lcp_hisoptions[ lns[linkunit].lcp_unit ];

	if (auth_required && !(go->neg_chap || go->neg_upap)) {


		if (!wo->neg_upap || !null_login(linkunit)) {
			syslog(LOG_WARNING, "peer refused to authenticate");
			lcp_close(lns[linkunit].lcp_unit,"peer refused to authenticate");
			lns[linkunit].phase = PHASE_TERMINATE;
			return;
		}
	}

	lns[linkunit].phase = PHASE_AUTHENTICATE;
	auth = 0;
	if (go->neg_chap) {
		ChapAuthPeer(lns[linkunit].chap_unit, our_name, go->chap_mdtype);
		auth |= CHAP_PEER;
	} else if (go->neg_upap) {
		upap_authpeer(lns[linkunit].upap_unit);
		auth |= UPAP_PEER;
	}
	if (ho->neg_chap) {
		ChapAuthWithPeer(lns[linkunit].chap_unit, our_name, ho->chap_mdtype);
		auth |= CHAP_WITHPEER;
	} else if (ho->neg_upap) {
		upap_authwithpeer(lns[linkunit].upap_unit, user, passwd);
		auth |= UPAP_WITHPEER;
	}
	lns[linkunit].auth_pending = auth;
	if (!auth)
		callback_phase(linkunit);
}
