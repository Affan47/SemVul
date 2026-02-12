unsigned long long get_global_cpu_statistics(struct activity *a, int prev, int curr,
					     unsigned int flags, unsigned char offline_cpu_bitmap[])
{
	int i;
	unsigned long long tot_jiffies_c, tot_jiffies_p;
	unsigned long long deltot_jiffies = 0;
	struct stats_cpu *scc, *scp;
	struct stats_cpu *scc_all = (struct stats_cpu *) ((char *) a->buf[curr]);
	struct stats_cpu *scp_all = (struct stats_cpu *) ((char *) a->buf[prev]);


	if (a->nr_ini > 1) {
		memset(scc_all, 0, sizeof(struct stats_cpu));
		memset(scp_all, 0, sizeof(struct stats_cpu));
	}

	for (i = 1; (i < a->nr_ini) && (i < a->bitmap->b_size + 1); i++) {


		scc = (struct stats_cpu *) ((char *) a->buf[curr] + i * a->msize);
		scp = (struct stats_cpu *) ((char *) a->buf[prev] + i * a->msize);


		tot_jiffies_c = scc->cpu_user + scc->cpu_nice +
				scc->cpu_sys + scc->cpu_idle +
				scc->cpu_iowait + scc->cpu_hardirq +
				scc->cpu_steal + scc->cpu_softirq;
		tot_jiffies_p = scp->cpu_user + scp->cpu_nice +
				scp->cpu_sys + scp->cpu_idle +
				scp->cpu_iowait + scp->cpu_hardirq +
				scp->cpu_steal + scp->cpu_softirq;


		if (tot_jiffies_c == 0) {


			*scc = *scp;


			offline_cpu_bitmap[i >> 3] |= 1 << (i & 0x07);
		}

		if ((tot_jiffies_p == 0) && !WANT_SINCE_BOOT(flags)) {


			offline_cpu_bitmap[i >> 3] |= 1 << (i & 0x07);
			continue;
		}


		deltot_jiffies += get_per_cpu_interval(scc, scp);

		scc_all->cpu_user += scc->cpu_user;
		scp_all->cpu_user += scp->cpu_user;

		scc_all->cpu_nice += scc->cpu_nice;
		scp_all->cpu_nice += scp->cpu_nice;

		scc_all->cpu_sys += scc->cpu_sys;
		scp_all->cpu_sys += scp->cpu_sys;

		scc_all->cpu_idle += scc->cpu_idle;
		scp_all->cpu_idle += scp->cpu_idle;

		scc_all->cpu_iowait += scc->cpu_iowait;
		scp_all->cpu_iowait += scp->cpu_iowait;

		scc_all->cpu_hardirq += scc->cpu_hardirq;
		scp_all->cpu_hardirq += scp->cpu_hardirq;

		scc_all->cpu_steal += scc->cpu_steal;
		scp_all->cpu_steal += scp->cpu_steal;

		scc_all->cpu_softirq += scc->cpu_softirq;
		scp_all->cpu_softirq += scp->cpu_softirq;

		scc_all->cpu_guest += scc->cpu_guest;
		scp_all->cpu_guest += scp->cpu_guest;

		scc_all->cpu_guest_nice += scc->cpu_guest_nice;
		scp_all->cpu_guest_nice += scp->cpu_guest_nice;
	}

	return deltot_jiffies;
}
