static bool igmp_heard_query(struct in_device *in_dev, struct sk_buff *skb,
	int len)
{
	struct igmphdr 		*ih = igmp_hdr(skb);
	struct igmpv3_query *ih3 = igmpv3_query_hdr(skb);
	struct ip_mc_list	*im;
	__be32			group = ih->group;
	int			max_delay;
	int			mark = 0;
	struct net		*net = dev_net(in_dev->dev);


	if (len == 8) {
		if (ih->code == 0) {


			max_delay = IGMP_QUERY_RESPONSE_INTERVAL;
			in_dev->mr_v1_seen = jiffies +
				(in_dev->mr_qrv * in_dev->mr_qi) +
				in_dev->mr_qri;
			group = 0;
		} else {

			max_delay = ih->code*(HZ/IGMP_TIMER_SCALE);
			in_dev->mr_v2_seen = jiffies +
				(in_dev->mr_qrv * in_dev->mr_qi) +
				in_dev->mr_qri;
		}

		in_dev->mr_ifc_count = 0;
		if (del_timer(&in_dev->mr_ifc_timer))
			__in_dev_put(in_dev);

		igmpv3_clear_delrec(in_dev);
	} else if (len < 12) {
		return true;
	} else if (IGMP_V1_SEEN(in_dev)) {

		max_delay = IGMP_QUERY_RESPONSE_INTERVAL;
		group = 0;
	} else if (IGMP_V2_SEEN(in_dev)) {


		max_delay = IGMPV3_MRC(ih3->code)*(HZ/IGMP_TIMER_SCALE);
		if (!max_delay)
			max_delay = 1;
	} else {
		if (!pskb_may_pull(skb, sizeof(struct igmpv3_query)))
			return true;

		ih3 = igmpv3_query_hdr(skb);
		if (ih3->nsrcs) {
			if (!pskb_may_pull(skb, sizeof(struct igmpv3_query)
					   + ntohs(ih3->nsrcs)*sizeof(__be32)))
				return true;
			ih3 = igmpv3_query_hdr(skb);
		}

		max_delay = IGMPV3_MRC(ih3->code)*(HZ/IGMP_TIMER_SCALE);
		if (!max_delay)
			max_delay = 1;
		in_dev->mr_maxdelay = max_delay;


		in_dev->mr_qrv = ih3->qrv ?: net->ipv4.sysctl_igmp_qrv;
		in_dev->mr_qi = IGMPV3_QQIC(ih3->qqic)*HZ ?: IGMP_QUERY_INTERVAL;


		if (in_dev->mr_qri >= in_dev->mr_qi)
			in_dev->mr_qri = (in_dev->mr_qi/HZ - 1)*HZ;

		if (!group) {
			if (ih3->nsrcs)
				return true;
			igmp_gq_start_timer(in_dev);
			return false;
		}

		mark = ih3->nsrcs != 0;
	}


	rcu_read_lock();
	for_each_pmc_rcu(in_dev, im) {
		int changed;

		if (group && group != im->multiaddr)
			continue;
		if (im->multiaddr == IGMP_ALL_HOSTS)
			continue;
		if (ipv4_is_local_multicast(im->multiaddr) &&
		    !net->ipv4.sysctl_igmp_llm_reports)
			continue;
		spin_lock_bh(&im->lock);
		if (im->tm_running)
			im->gsquery = im->gsquery && mark;
		else
			im->gsquery = mark;
		changed = !im->gsquery ||
			igmp_marksources(im, ntohs(ih3->nsrcs), ih3->srcs);
		spin_unlock_bh(&im->lock);
		if (changed)
			igmp_mod_timer(im, max_delay);
	}
	rcu_read_unlock();
	return false;
}
