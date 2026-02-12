void get_global_soft_statistics(struct activity *a, int prev, int curr,
				unsigned int flags, unsigned char offline_cpu_bitmap[])
{
	int i;
	struct stats_softnet *ssnc, *ssnp;
	struct stats_softnet *ssnc_all = (struct stats_softnet *) ((char *) a->buf[curr]);
	struct stats_softnet *ssnp_all = (struct stats_softnet *) ((char *) a->buf[prev]);


	memset(ssnc_all, 0, sizeof(struct stats_softnet));
	memset(ssnp_all, 0, sizeof(struct stats_softnet));

	for (i = 1; (i < a->nr_ini) && (i < a->bitmap->b_size + 1); i++) {


                ssnc = (struct stats_softnet *) ((char *) a->buf[curr] + i * a->msize);
                ssnp = (struct stats_softnet *) ((char *) a->buf[prev] + i * a->msize);

		if (ssnc->processed + ssnc->dropped + ssnc->time_squeeze +
		    ssnc->received_rps + ssnc->flow_limit == 0) {

			*ssnc = *ssnp;
			offline_cpu_bitmap[i >> 3] |= 1 << (i & 0x07);
		}

		if ((ssnp->processed + ssnp->dropped + ssnp->time_squeeze +
		    ssnp->received_rps + ssnp->flow_limit == 0) && !WANT_SINCE_BOOT(flags)) {

			offline_cpu_bitmap[i >> 3] |= 1 << (i & 0x07);
			continue;
		}

		ssnc_all->processed += ssnc->processed;
		ssnc_all->dropped += ssnc->dropped;
		ssnc_all->time_squeeze += ssnc->time_squeeze;
		ssnc_all->received_rps += ssnc->received_rps;
		ssnc_all->flow_limit += ssnc->flow_limit;

		ssnp_all->processed += ssnp->processed;
		ssnp_all->dropped += ssnp->dropped;
		ssnp_all->time_squeeze += ssnp->time_squeeze;
		ssnp_all->received_rps += ssnp->received_rps;
		ssnp_all->flow_limit += ssnp->flow_limit;
	}
}
