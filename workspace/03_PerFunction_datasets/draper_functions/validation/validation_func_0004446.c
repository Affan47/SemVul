get_station(struct wiphy *wiphy, struct net_device *dev,
		       const u8 *mac, struct station_info *sinfo)
{
	struct wilc_priv *priv;
	perInterface_wlan_t *nic;
	u32 i = 0;
	u32 associatedsta = 0;
	u32 inactive_time = 0;
	priv = wiphy_priv(wiphy);
	nic = netdev_priv(dev);

	if (nic->iftype == AP_MODE || nic->iftype == GO_MODE) {
		PRINT_D(HOSTAPD_DBG, "Getting station parameters\n");

		PRINT_INFO(HOSTAPD_DBG, ": %x%x%x%x%x\n", mac[0], mac[1], mac[2], mac[3], mac[4]);

		for (i = 0; i < NUM_STA_ASSOCIATED; i++) {

			if (!(memcmp(mac, priv->assoc_stainfo.au8Sta_AssociatedBss[i], ETH_ALEN))) {
				associatedsta = i;
				break;
			}

		}

		if (associatedsta == -1) {
			PRINT_ER("Station required is not associated\n");
			return -ENOENT;
		}

		sinfo->filled |= BIT(NL80211_STA_INFO_INACTIVE_TIME);

		host_int_get_inactive_time(priv->hWILCWFIDrv, mac, &(inactive_time));
		sinfo->inactive_time = 1000 * inactive_time;
		PRINT_D(CFG80211_DBG, "Inactive time %d\n", sinfo->inactive_time);

	}

	if (nic->iftype == STATION_MODE) {
		struct rf_info strStatistics;

		host_int_get_statistics(priv->hWILCWFIDrv, &strStatistics);

		sinfo->filled |= BIT(NL80211_STA_INFO_SIGNAL) |
						BIT(NL80211_STA_INFO_RX_PACKETS) |
						BIT(NL80211_STA_INFO_TX_PACKETS) |
						BIT(NL80211_STA_INFO_TX_FAILED) |
						BIT(NL80211_STA_INFO_TX_BITRATE);

		sinfo->signal		=  strStatistics.s8RSSI;
		sinfo->rx_packets   =  strStatistics.u32RxCount;
		sinfo->tx_packets   =  strStatistics.u32TxCount + strStatistics.u32TxFailureCount;
		sinfo->tx_failed	=  strStatistics.u32TxFailureCount;
		sinfo->txrate.legacy = strStatistics.u8LinkSpeed * 10;

		if ((strStatistics.u8LinkSpeed > TCP_ACK_FILTER_LINK_SPEED_THRESH) && (strStatistics.u8LinkSpeed != DEFAULT_LINK_SPEED))
			Enable_TCP_ACK_Filter(true);
		else if (strStatistics.u8LinkSpeed != DEFAULT_LINK_SPEED)
			Enable_TCP_ACK_Filter(false);

		PRINT_D(CORECONFIG_DBG, "*** stats[%d][%d][%d][%d][%d]\n", sinfo->signal, sinfo->rx_packets, sinfo->tx_packets,
			sinfo->tx_failed, sinfo->txrate.legacy);
	}
	return 0;
}
