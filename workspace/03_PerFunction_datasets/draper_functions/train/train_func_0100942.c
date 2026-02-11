preset_ethernet()
{

	safe_strncpy(ETH(0, type), XIF_TYPE, sizeof(ETH(0, type)));
	safe_strncpy(ETH(0, tunnel), XIF_TUNNEL, sizeof(ETH(0, tunnel)));
	safe_strncpy(ETH(0, ip_host), XIF_HOST_IP, sizeof(ETH(0, ip_host)));
	safe_strncpy(ETH(0, ip_atari), XIF_ATARI_IP, sizeof(ETH(0, ip_atari)));
	safe_strncpy(ETH(0, netmask), XIF_NETMASK, sizeof(ETH(0, netmask)));
	safe_strncpy(ETH(0, mac_addr), XIF_MAC_ADDR, sizeof(ETH(0, mac_addr)));


	for(int i=1; i<MAX_ETH; i++) {
		*ETH(i, type) = '\0';
		*ETH(i, tunnel) = '\0';
		*ETH(i, ip_host) = '\0';
		*ETH(i, ip_atari) = '\0';
		*ETH(i, netmask) = '\0';
		*ETH(i, mac_addr) = '\0';
	}
}
