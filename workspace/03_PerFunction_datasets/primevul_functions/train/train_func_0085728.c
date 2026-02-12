syn_cache_unreach(struct sockaddr *src, struct sockaddr *dst, struct tcphdr *th,
    u_int rtableid)
{
	struct syn_cache *sc;
	struct syn_cache_head *scp;

	NET_ASSERT_LOCKED();

	if ((sc = syn_cache_lookup(src, dst, &scp, rtableid)) == NULL)
		return;

	if (ntohl (th->th_seq) != sc->sc_iss) {
		return;
	}


	if ((sc->sc_flags & SCF_UNREACH) == 0 || sc->sc_rxtshift < 3) {
		sc->sc_flags |= SCF_UNREACH;
		return;
	}

	syn_cache_rm(sc);
	tcpstat_inc(tcps_sc_unreach);
	syn_cache_put(sc);
}
