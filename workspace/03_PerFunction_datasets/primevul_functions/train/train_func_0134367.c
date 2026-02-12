static unsigned int _rtl_rx_get_padding(struct ieee80211_hdr *hdr,
					unsigned int len)
{
#if NET_IP_ALIGN != 0
	unsigned int padding = 0;
#endif


	if (NET_IP_ALIGN == 0 || len < sizeof(*hdr))
		return 0;

#if NET_IP_ALIGN != 0


	if (ieee80211_is_data_qos(hdr->frame_control)) {
		u8 *qc = ieee80211_get_qos_ctl(hdr);

		padding ^= NET_IP_ALIGN;


		if ((unsigned long)qc - (unsigned long)hdr < len &&
		    *qc & IEEE80211_QOS_CTL_A_MSDU_PRESENT)
			padding ^= NET_IP_ALIGN;
	}

	if (ieee80211_has_a4(hdr->frame_control))
		padding ^= NET_IP_ALIGN;

	return padding;
#endif
}
