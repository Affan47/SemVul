static inline int is_same_network(struct bss_descriptor *src,
				  struct bss_descriptor *dst)
{


	return ((src->ssid_len == dst->ssid_len) &&
		(src->channel == dst->channel) &&
		!compare_ether_addr(src->bssid, dst->bssid) &&
		!memcmp(src->ssid, dst->ssid, src->ssid_len));
}
