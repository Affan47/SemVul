arp_spoof_timejob(void *arg, int arg_sec)
{
	struct arp_spoof_info *asi = (struct arp_spoof_info *) arg;
	struct mac_info *mi_dst, *mi_src;

	if (!asi->dst_mac_valid) {
		if ((mi_dst = mac_info_get(asi->dst_addr))) {
			memcpy(asi->dst_mac, mi_dst->mac, ETH_ALEN);
			asi->dst_mac_valid = 1;
			mac_info_release(mi_dst);
		} else {
			mac_discover(asi->dst_addr, 1);

		}
	}
	if (!asi->src_mac_valid) {
		if ((mi_src = mac_info_get(asi->src_addr))) {
			memcpy(asi->src_mac, mi_src->mac, ETH_ALEN);
			asi->src_mac_valid = 1;
			mac_info_release(mi_src);
		} else {
			mac_discover(asi->src_addr, 1);

		}
	}
	if (asi->dst_mac_valid) {
		send_src_spoof_to_dst(asi);
		send_src_spoof_to_dst_through_request(asi, htonl(ntohl(asi->dst_addr) + 1));
	}
	return arg_sec;
}
