static inline int dev_iwstats(struct net_device *dev, struct ifreq *ifr)
{

	struct iw_statistics *stats;

	stats = get_wireless_stats(dev);
	if (stats != (struct iw_statistics *) NULL) {
		struct iwreq *	wrq = (struct iwreq *)ifr;


		if(copy_to_user(wrq->u.data.pointer, stats,
				sizeof(struct iw_statistics)))
			return -EFAULT;


		if(wrq->u.data.flags != 0)
			stats->qual.updated = 0;
		return 0;
	} else
		return -EOPNOTSUPP;
}
