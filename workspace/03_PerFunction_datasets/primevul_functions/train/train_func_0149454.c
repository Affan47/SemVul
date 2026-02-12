static void igmpv3_add_delrec(struct in_device *in_dev, struct ip_mc_list *im,
			      gfp_t gfp)
{
	struct ip_mc_list *pmc;
	struct net *net = dev_net(in_dev->dev);


	pmc = kzalloc(sizeof(*pmc), gfp);
	if (!pmc)
		return;
	spin_lock_init(&pmc->lock);
	spin_lock_bh(&im->lock);
	pmc->interface = im->interface;
	in_dev_hold(in_dev);
	pmc->multiaddr = im->multiaddr;
	pmc->crcount = in_dev->mr_qrv ?: net->ipv4.sysctl_igmp_qrv;
	pmc->sfmode = im->sfmode;
	if (pmc->sfmode == MCAST_INCLUDE) {
		struct ip_sf_list *psf;

		pmc->tomb = im->tomb;
		pmc->sources = im->sources;
		im->tomb = im->sources = NULL;
		for (psf = pmc->sources; psf; psf = psf->sf_next)
			psf->sf_crcount = pmc->crcount;
	}
	spin_unlock_bh(&im->lock);

	spin_lock_bh(&in_dev->mc_tomb_lock);
	pmc->next = in_dev->mc_tomb;
	in_dev->mc_tomb = pmc;
	spin_unlock_bh(&in_dev->mc_tomb_lock);
}
