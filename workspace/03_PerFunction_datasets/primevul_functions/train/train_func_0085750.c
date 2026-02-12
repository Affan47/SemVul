syn_cache_insert(struct syn_cache *sc, struct tcpcb *tp)
{
	struct syn_cache_set *set = &tcp_syn_cache[tcp_syn_cache_active];
	struct syn_cache_head *scp;
	struct syn_cache *sc2;
	int i;

	NET_ASSERT_LOCKED();


	if (set->scs_count == 0 && set->scs_use <= 0) {
		set->scs_use = tcp_syn_use_limit;
		if (set->scs_size != tcp_syn_hash_size) {
			scp = mallocarray(tcp_syn_hash_size, sizeof(struct
			    syn_cache_head), M_SYNCACHE, M_NOWAIT|M_ZERO);
			if (scp == NULL) {

				set->scs_use = 0;
			} else {
				free(set->scs_buckethead, M_SYNCACHE,
				    set->scs_size *
				    sizeof(struct syn_cache_head));
				set->scs_buckethead = scp;
				set->scs_size = tcp_syn_hash_size;
				for (i = 0; i < tcp_syn_hash_size; i++)
					TAILQ_INIT(&scp[i].sch_bucket);
			}
		}
		arc4random_buf(set->scs_random, sizeof(set->scs_random));
		tcpstat_inc(tcps_sc_seedrandom);
	}

	SYN_HASHALL(sc->sc_hash, &sc->sc_src.sa, &sc->sc_dst.sa,
	    set->scs_random);
	scp = &set->scs_buckethead[sc->sc_hash % set->scs_size];
	sc->sc_buckethead = scp;


	if (scp->sch_length >= tcp_syn_bucket_limit) {
		tcpstat_inc(tcps_sc_bucketoverflow);


		set->scs_use = 0;


		sc2 = TAILQ_FIRST(&scp->sch_bucket);
#ifdef DIAGNOSTIC


		if (sc2 == NULL)
			panic("%s: bucketoverflow: impossible", __func__);
#endif
		syn_cache_rm(sc2);
		syn_cache_put(sc2);
	} else if (set->scs_count >= tcp_syn_cache_limit) {
		struct syn_cache_head *scp2, *sce;

		tcpstat_inc(tcps_sc_overflowed);


		scp2 = scp;
		if (TAILQ_EMPTY(&scp2->sch_bucket)) {
			sce = &set->scs_buckethead[set->scs_size];
			for (++scp2; scp2 != scp; scp2++) {
				if (scp2 >= sce)
					scp2 = &set->scs_buckethead[0];
				if (! TAILQ_EMPTY(&scp2->sch_bucket))
					break;
			}
#ifdef DIAGNOSTIC


			if (scp2 == scp)
				panic("%s: cacheoverflow: impossible",
				    __func__);
#endif
		}
		sc2 = TAILQ_FIRST(&scp2->sch_bucket);
		syn_cache_rm(sc2);
		syn_cache_put(sc2);
	}


	sc->sc_rxttot = 0;
	sc->sc_rxtshift = 0;
	SYN_CACHE_TIMER_ARM(sc);


	LIST_INSERT_HEAD(&tp->t_sc, sc, sc_tpq);


	TAILQ_INSERT_TAIL(&scp->sch_bucket, sc, sc_bucketq);
	scp->sch_length++;
	sc->sc_set = set;
	set->scs_count++;
	set->scs_use--;

	tcpstat_inc(tcps_sc_added);


	if (set->scs_use <= 0 &&
	    tcp_syn_cache[!tcp_syn_cache_active].scs_count == 0)
		tcp_syn_cache_active = !tcp_syn_cache_active;
}
