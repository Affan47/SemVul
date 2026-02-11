get_ethtool_ipv6_rss(struct bnxt *bp)
{
	if (bp->rss_hash_cfg & VNIC_RSS_CFG_REQ_HASH_TYPE_IPV6)
		return RXH_IP_SRC | RXH_IP_DST;
	return 0;
}
