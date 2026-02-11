check_for_socket_match(struct lro *lro, struct iphdr *ip,
				  struct tcphdr *tcp)
{
	DBG_PRINT(INFO_DBG, "%s: Been here...\n", __func__);
	if ((lro->iph->saddr != ip->saddr) ||
	    (lro->iph->daddr != ip->daddr) ||
	    (lro->tcph->source != tcp->source) ||
	    (lro->tcph->dest != tcp->dest))
		return -1;
	return 0;
}
