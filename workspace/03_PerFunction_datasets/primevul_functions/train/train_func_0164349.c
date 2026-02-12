static inline int is_same_network(struct ieee80211_network *src,
				  struct ieee80211_network *dst)
{


	return ((src->ssid_len == dst->ssid_len) &&
		(src->channel == dst->channel) &&
		!compare_ether_addr(src->bssid, dst->bssid) &&
		!memcmp(src->ssid, dst->ssid, src->ssid_len));
}
